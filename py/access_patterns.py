import os
import matplotlib.pyplot as plt
import math
import numpy as np
import sys

from dataclasses import dataclass
from enum import Enum, auto
from scipy.stats import zipfian, randint

FILENAME = os.path.join(os.path.dirname(os.path.realpath('__file__')), '../config')
FOUT = 'patterns/pattern'
ASSIGN = '='
COMMENT = '#'
PATTERNNR = 0
PLOTDIST = False
PLOTSCATTER = True
VERBOSE = True

class Pattern(Enum):
    RANDOM = auto()
    SEQUENTIAL = auto()
    STRIDED = auto()
    LADDER = auto()
    
class Distribution(Enum):
    ZIPFIAN = auto()
    UNIFORM = auto()

@dataclass
class Config:
    """Config structure for memory access indexing""" 
    num_of_addresses: int
    num_of_accesses: int
    num_of_random: int = 0
    num_of_sequential: int = 0
    num_of_strided: int = 0
    num_of_ladder: int = 0
    distribution: Distribution = Distribution.ZIPFIAN
    pattern: Pattern = Pattern.SEQUENTIAL
    pattern_length: int = 0
    stride: int = 1
    zipfian_alpha: float = 4.0
    size_of_element: int = 8
    access_type: str = 'rw'
    strict: bool = False
    reuse : bool = False

    def __init__(self):
        fh = open(FILENAME, 'r')
        line = fh.readline()
        while line:
            if ASSIGN in line and line[0] != COMMENT:
                [field, val] = split_line(line)
                match field:
                    case 'distribution':
                        self.distribution = Distribution[val]
                    case 'param_pattern_length':
                        self.pattern_length = int(val)
                    case 'param_stride':
                        self.stride = int(val)
                    case 'pattern_strided':
                        self.num_of_strided = int(val)//10
                    case 'pattern_sequential':
                        self.num_of_sequential = int(val)//10
                    case 'pattern_random':
                        self.num_of_random = int(val)//10
                    case 'pattern_ladder':
                        self.num_of_ladder = int(val)//10
                    case 'zipfian_alpha':
                        self.zipfian_alpha = float(val)
                    case 'param_pattern_length':
                        self.pattern_length = int(val)
                    case 'size_of_element':
                        self.size_of_element = parse_int(val)
                    case 'access_type':
                        self.access_type = val
                    case 'memory':
                        self.memory = parse_int(val)
                    case 'strict_patterns':
                        self.strict = val.lower() == 'true'
                    case 'reuse_patterns':
                        self.reuse = val.lower() == 'true'
                    case 'num_accesses':
                        self.num_of_accesses = int(val)
                    case 'threads':
                        self.threads = int(val)
                    case _:
                        print(f"Unknown field: {field}")
            line = fh.readline()
        fh.close()
        self.num_of_addresses = self.memory // self.size_of_element

        
def parse_int(val): 
    multiplicants = val.split('*')
    val = 1
    for m in multiplicants:
           val *= int(m)
    return val
    
    
def split_line(line): 
    [field, val] = line.split(ASSIGN)
    if COMMENT in val:
        [val, _] = val.split(COMMENT)
    field = field.strip()
    val = val.strip()
    return [field, val]


def refresh_count(cfg: Config):
    return [cfg.num_of_sequential, cfg.num_of_strided, 
            cfg.num_of_ladder, cfg.num_of_random]


def count_elements(l):
    count = 0
    for elem in l:
        count += len(elem)
    return count
    

def potential_set(samples: list, cfg: Config):
    """Returns a set of potential indices needed to form the specified pattern"""   
    if cfg.pattern == Pattern.STRIDED:
        pattern_step = cfg.stride
    else:
        pattern_step = 1
        
    def potential_samples(s: int):
        ret = set()
        for position in range(cfg.pattern_length):
            ret.add((s - position*pattern_step) % cfg.num_of_addresses)
        for position in range(cfg.pattern_length):
            ret.add((s + position*pattern_step) % cfg.num_of_addresses)
        ret.remove(s)
        return ret

    potentials = set()
    if len(samples) == cfg.pattern_length:
        # Pattern already completed
        return potentials
    
    for s in samples:
        if len(potentials) == 0:
            potentials = potential_samples(s)
        else: 
            potentials = potentials.intersection(potential_samples(s))
    return potentials


def generate_pattern(cfg: Config):
    """Generates specified memory access pattern and writes it to FOUT"""
    pattern_list = list()
    num_of_hot_regions = 2
    for region in range(num_of_hot_regions):
        # Generate random numbers
        if cfg.distribution == Distribution.ZIPFIAN:
            s = zipfian.rvs(cfg.zipfian_alpha, cfg.num_of_addresses, size=cfg.num_of_accesses)
        elif cfg.distribution == Distribution.UNIFORM:
            s = randint.rvs(low=1, high=cfg.num_of_addresses+1, size=cfg.num_of_accesses)
        samples = s.tolist()
        samples = [s-1 for s in samples] # Let's start indexing at 0
        
        # Distribute addresses around the most popular address
        popular_address = randint.rvs(low=0, high=cfg.num_of_addresses)
        addresses = [(( (-1)**(i+1) ) * math.ceil(i/2) + popular_address) % cfg.num_of_addresses 
                     for i in range(cfg.num_of_addresses)]
        
        # Arange according to the desired pattern
        pattern_list += arange_samples(samples, addresses, cfg)
    
    np.random.shuffle(pattern_list) # Merge patterns
    write_to_file(pattern_list, cfg)
    
    if PLOTSCATTER:
        plot_pattern(pattern_list, cfg)
    
    if PLOTDIST: # Plot sample distribution
        a = cfg.zipfian_alpha
        n = cfg.num_of_addresses
        count = np.bincount(s)
        k = np.arange(1, s.max() + 1)
        plt.bar(k, count[1:], alpha=0.5, label='sample count')
        # plt.plot(k, n*(k**-a)/zeta(a), 'k.-', alpha=0.5,
        #          label='expected count')   
        plt.semilogy()
        plt.grid(alpha=0.4)
        plt.legend()
        plt.title(f'Zipf sample, a={a}, size={n}')
        plt.show()


def plot_pattern(pattern_list: list, cfg: Config):
    x = list()
    y = list()
    c = list()
    count = 1
    for pattern in pattern_list:
        for e in pattern:
            c.append(len(pattern))
            y.append(e)
            x.append(count)
            count += 1
        
    fig, ax = plt.subplots()
    scatter = ax.scatter(x,y, c=c)
    legend1 = ax.legend(*scatter.legend_elements(),
                    loc="upper right", title="pattern length")
    plt.show()


def arange_samples(samples, addresses, cfg: Config):
    """Returns a list of lists with indices that each follow the specified pattern"""
    pattern_lists = list()
    incomplete_lists = list()
    
    if cfg.pattern == Pattern.RANDOM:
        samples = [addresses[sample] for sample in samples]
        return [samples[i:i + cfg.pattern_length] for i in range(0, len(samples), cfg.pattern_length)]
    
    [num_seq, num_stride, num_ladder, num_rand] = refresh_count(cfg)

    while len(samples):
        if num_seq == 0 and num_stride == 0 and num_ladder == 0 and num_rand == 0:
            [num_seq, num_stride, num_ladder, num_rand] = refresh_count(cfg)
        
        if num_seq > 0:
            cfg.pattern = Pattern.SEQUENTIAL
        elif num_stride > 0:
            cfg.pattern = Pattern.STRIDED
        elif num_ladder > 0:
            cfg.pattern = Pattern.STRIDED
        elif num_rand > 0:
            cfg.pattern = Pattern.RANDOM
            
        pattern_list = list()
        if cfg.pattern == Pattern.RANDOM:
            for _ in range(cfg.pattern_length):
                try:
                    pattern_list.append(addresses[samples.pop()])
                except:
                    break # This is fine.
            if len(pattern_list) == cfg.pattern_length:
                pattern_lists.append(pattern_list)
            num_rand -= 1
            continue
        
        sample = samples.pop()
        pattern_list = [addresses[sample]]
        needed_for_pattern = potential_set(pattern_list, cfg)
        while len(needed_for_pattern):
            index = None
            for i, val in enumerate(samples):
                if addresses[val] in needed_for_pattern:
                    index = i
                    break
            if index is None:
                # No fitting sample found
                pattern_list.sort()
                incomplete_lists.append(pattern_list)
                match cfg.pattern:
                    case Pattern.SEQUENTIAL:
                        num_seq -= 1
                    case Pattern.STRIDED:
                        num_stride -= 1
                    case Pattern.LADDER:
                        num_ladder -= 1

                break
            
            pattern_list.append(addresses[samples.pop(index)])
            needed_for_pattern = potential_set(pattern_list, cfg)
        
        if not len(needed_for_pattern):
            # pattern_list is a complete pattern
            pattern_list.sort()
            pattern_lists.append(pattern_list)
            match cfg.pattern:
                case Pattern.SEQUENTIAL:
                    num_seq -= 1
                case Pattern.STRIDED:
                    num_stride -= 1
                case Pattern.LADDER:
                    num_ladder -= 1

    if VERBOSE:
        print(f"Incomplete size: {count_elements(incomplete_lists)}")
        print(f"Complete size: {count_elements(pattern_lists)}")

    if not cfg.strict:
        # Non-strict mode: distribute incomplete patterns over pattern_list
        for incomplete_pattern in incomplete_lists:
            index = randint.rvs(low=0, high=len(pattern_lists))
            pattern_lists.insert(index, incomplete_pattern)
    
    return pattern_lists
        
 
def write_to_file(pattern_list: list, cfg: Config):
    """Write memory access pattern to file"""
    global PATTERNNR
    with open(f"{FOUT}_{PATTERNNR}_{cfg.pattern.name}", 'w') as fh:
        PATTERNNR += 1
        fh.write(f"{cfg.memory} {cfg.size_of_element} {cfg.threads} {cfg.access_type}\n")    # Fileheader
        for pattern in pattern_list:
            fh.write(f"{pattern}\n")


if __name__ == "__main__":
    cfg = Config()
    print(cfg)
    if cfg.reuse:
        sys.exit()
    generate_pattern(cfg)
