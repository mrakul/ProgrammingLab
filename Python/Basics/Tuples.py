# Tuple examples
T = ([2, 4], 5)     # tuples can contain lists
T[0].remove(2)      # and lists even cant be changed
T[0].remove(4)
# T[0] = 1              # But can't change item type, item assignment is restricted

# Tuple can be used as a key, unless has unhashable items
D = {}
D[(1, 2)] = "Value1"
print(D)
# D[(1, [])]  = "Value2"    # Can't be performed, list is unhashable


# Named tuple example
from collections import namedtuple
Rec = namedtuple('Rec', ['name', 'age', 'jobs'])

bob = Rec('Bob', age=40.5, jobs=['dev', 'mgr'])
print(bob)
# Use indexing
print(bob[0])

# Use as dictionary
print(bob._asdict()['name'] + ' ' + str(bob._asdict()['age']) + ' ' + str(bob._asdict()['jobs']))