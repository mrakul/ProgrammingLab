# Dictionary basics
D1 = {'1' : [1, 2, 3], 2 : (7, 8, 9)}
D1.keys()

# Find key and get value
print(D1.get('1'))
print(D1.get(3))    # => None

# Merge
# D2 = {[1, 2] : "Test"}    # => Restricted, List is not hashable object
D2 = {4 : "Test"}
D1.update(D2)

# Print out keys, values, pairs of "key: value"
# Note: need to use list() constructor to have a list. Although, it returns dict_values, _keys, items type is returned (and it is also iterable)
print(list(D1.keys()))
print(list(D1.values()))
print(list(D1.items())) # => returns tuple

# Set default value and pop item
D1.setdefault(6, "NO VALUE")  # => fetch by key, if absent set default (or None),
print(D1.get(6))
print(6 in D1)
print(D1.popitem())           # => return item as a tuple

D1[7] = "Value"
D1.setdefault("200", "Test")

# Print keys having particular value
print([key for key in D1.keys() if D1[key] == "Test"])

# Create using zip function
list(zip(['a', 'b', 'c'], [1, 2, 3]))
D2 = dict(zip(['a', 'b', 'c'], [1, 2, 3]))

# Or use comprehensions
D3 = {x: x ** 2 for x in [1, 2, 3, 4]}
D3 = dict.fromkeys(['a', 'b', 'c'], 0)
D3 = {k : 0 for k in ['a', 'b', 'c']}
D3 = dict.fromkeys('spam')
D3 = {k : None for k in 'spam'}

D3.keys() & {'a' : 200}     # => supports set operations (intersection and so on)
# D3.values() & {'b' : 0}     # => Error, not a set (dict_values vs dict)

print(D3)
