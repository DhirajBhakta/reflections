TODO: break this up into files


tips:
- `[::-1]` to reverse
- `[:]` to make copy
## Data types
To get datatype `print(type(var))`
To get size `sys.getsizeof(val)`
- Lists
	- Allows different datatypes in same list
	- `list[-1]` is last item, `list[-2]` is second last item...
	- `len(list)` gives length
	- `list.append(val)` for append
	- `list.count(val)` gives number of occurrences of val
	- `list.index(val)` gives index of first occurrence of val
	- `list.pop()` gives last element and REMOVES it
	- `list.remove(val)` removes value from list (from anywhere)
	- `list.clear()` empties the list
	- `list.reverse()` and `list.sort()` ..obv
	- `list = [0]*5` list with 5 zeroes
	- `new_list = list + list2` concatenation
	- Slicing: 
		- `list[1:5]` (incl,excl)..
		- `list[:]` makes a copy
		- (actually its `list[1:5:1]` the last value is step index).. 
		- `list[::1]` makes a copy (`list(mylist)` also makes a copy)
		- `list[::2]` takes every second element 
		- `list[::-1]` reverses the list !
	- Unpacking:
		- `i1, *i2, i3 = my_list` then i1 and i3 are first and last items. i2 is a list of everything in between
	- Sorting:
		- `new_list = sorted(list, key=lambda x: x)`
	- Functional programming: map,  filter, reduce
		- `new_list = list(map(lambda x: x*2, list))`
		- `new_list = list(filter(lambda x: x%2==0,a))`
		- `from functools import reduce` ....
			- `value = reduce(lambda acc,curr: acc*curr, list))`
- Tuples
	- Tuple from List: `tuple(list)`
	- tuple can be used as a key in Dict (but list is not hashable)
- Dicts
	- `del mydict["key"]` to remove a key . || or use `mydict.pop(key)`
	- `mydict.popitem()` removes the last inserted key
	- `new_dict = mydict.copy()` to make copy or use `dict(mydict)`
	- `mydict.update(mydict2)` merge 2 dicts
	- tuple can be used as a key in Dict
	- Since py3.7 Dict is same as OrderedDict in `collections`, i.e it remembers the order of keys!
- Sets
	- `myset = {1,2,3,4}`
	- `new_set = myset.copy()` to make copy or use `set(myset)`
	- `myset.add(val)`
	- `myset.remove(val)` or `myset.discard(val)` to remove from set
	- `myset.clear()` empties the set.
	- `myset.update(otherset)` add values from other set (INPLACE)
	- `myset.intersection_update(otherset)` keep only intersection (INPLACE)
	- `myset.difference_update(otherset)` keep only difference update (INPLACE)
	- UNION of 2 sets: `myset.union(otherset)`
	- INTERSECTION: `myset.intersection(otherset)`
	- DIFFERENCE: `myset.difference(otherset)`
	- SYMMETRIC DIFFERENCE: present in A and B but not in both, `myset.symmetric_difference(otherset)`
	- `myset.issubset(otherset)` and `myset.issuperset(otherset)`
	- `myset.isdisjoint(otherset)`
- Strings
	- IMMUTABLE!
	- `my_str.strip()` whitespaces from either end
	- `my_str.upper()` and `my_str.lower()`
	- `my_str.startswith("Hell")` and `my_str.endswith("orld")`
	- `my_str.find('c')` get the index of first occurrence
	- `my_str.count('c')` count occurrence
	- `my_str.split(",")`  or `" ".join(my_str.split(",")`


## Collections
- Counter
	- `from collections import Counter`
	- `ctr = Counter("aaaaabbbccccc")` is a Dict
	- `ctr.most_common(2)` 2 most common values?
- namedtuple
	- `from collections import namedtuple`
	- `Point = namedtuple('Point','x,y')`
		- `pt = Point(1,2)`
		- `print(pt.x , pt.y)`
- defaultdict
	- `from collections import defaultdict`
	- `d = defaultdict(list)`
- deque
	- `from collections import deque`
	- `d = deque()`
	- `d.append(1)` and `d.appendleft(2)`
	- `d.pop()` and `d.popleft()`
	- `d.clear()` to remove all elements
	- `d.extend([4,5,6])` and `d.extendleft([4,5,6])`
	- `d.rotate(1)` or `d.rotate(-1)`

## Itertools
- Product
	- `from itertools import product`
	- gets you cartesian product of 2 lists
	- `print(list(product([1,2] , [3,4])))`
- Permutations and Combinations
	- `from itertools import permutations, combinations`
	- `print(list(permutations([1,2,3])))`
- accumulate
	- `from itertools import accumulate`
	- constructs a prefix sum of sorts...
	- `print(list(accumulate([1,2,3,4])))`
- groupby
	- `from itertools import groupby`
	- `groupby([1,2,3,4], key=lambda x: x<3)`

## Exception
`raise Exception("some error occurred")`

```py
class CustomError(Exception)
	pass

class CustomError(Exception)
	def __init__(self, message, value):
	     self.message = message
	     self.value = value
```


## Logging
TODO!
debug, info, warning, error, critical
- default loglevel=warning
- `logging.basicConfig(level=logging.DEBUG)`

#### Creating your own logger
```py
import logging
logger = logging.getLogger(__name__)
logger.info("first log")
```
All new loggers form a hierarchy, under the root logger. and the logs will flow up the hierarchy. If you dont want that, `logger.propagate=False`

#### Handler:
```py
stream_h = logging.StreamHandler()
file_h = logging.FileHandler('file.log')
```

TODO: `from logging.handlers import RotatingFileHandler, TimedRotatingFileHandler`


#### Formatter:

#### Printing stack trace:


## JSON
TODO: encoding a class's obj into json, decoding json into class obj
you need custom encoding function(hint: convert to dict first) or use JSONEncoder


## Random
TODO
`random.seed()`


## Decorators
_a function that takes another func and returns a func_

```py
def start_end_decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
          print("start")
          res = func(*args, **kwargs)
          print("end")
          return res
    return wrapper

@start_end_decorator
def print_name(name):
    print(name)
```


TODO decorator with arguments 
TODO class based decorators (to count the number of function calls)


## Generators
TODO
Memory efficient
```py
def mygenerator():
	yield 1
	yield 2
	yield 3

g = mygenerator()

val = next(g)
# raises StopIteration
```

```py
def fibonacci(limit):
	a,b = 0,1
	while a<limit:
		yield a
		a,b = b, a+b
```

```py
mygenerator = (i for i in range(10) if i%2==0)
```

## MultiThreading and MultiProcessing
TODO
why GIL was required?: cuz of reference counting implementation in GC

CPU bound?: use multiprocessing
IO bound?: use multithreading

TODO: `from threading import Lock`


## Asynchronous Programming
asyncio anyio uvloop | gevent
C     => libuv libev | gevent
LINUX => select, poll, epoll, io_uring




## Performance
timing
```python
import timeit
print(timeit.timeit(stmt="[1,2,3]",number=1000000))
```
