# A first Python script
import sys
import os
import math
import random
import re

# Main built-in functions
# Print out description about passed object
help(list)
help(list.append)
A = []
help(A)

# Returns the attributes of the passed object
dir(list)
dir(A)

# Returns the type of the object (where the name references)
type(A)

# The Zen of Python, by Tim Peters
import this

# Print OS name
print(sys.platform)
print(os.getcwd())

# Print 2^32
print('2^32: '  +  str(2 ** 32) + ' bytes')

# String repetition
x = 'Spam! '
print(x * 8)

# Math example
print(math.pi)
print(random.randint(10, 20))

# String examples>>> line = 'aaa,bbb,ccccc,dd'
myString = 'Spam'
print(myString.find('pa'))
print(myString)

print(myString.replace('pa', 'XYZ'))
print(myString)

# Find the offset of a substring in myString
line = 'aaa,bbb,ccccc,dd'
print(line.split(','))
print(myString.upper())
print(myString.isalpha())
print(myString.isdecimal())

# Split on a delimiter into a list of substrings
line = 'aaa,bbb,ccccc,dd\n'
#print line with additional NewLine in the text (from the right side)
print(line)
# print line without whitespace characters
print(line.rstrip())

# Remove whitespace characters and 
print(line.rstrip().split(','))

# Regular Expressions
match = re.match('Hello[ \t]*(.*)world', 'Hello   world')
match.group(1)

# List examples
myList = [1, "Test", [2, 4, 5]]
print(myList)

myList.pop(2)
print(myList)

myList.reverse()
print(myList)

myList.append("END")
print(myList)

# Matrix
matrix = [[1,2,3],[4,5,6],[7,8,9]]
print(matrix)

print(list(range(4)))
# −6 to +6 by 2 (need list() in 3.X)
print(list(range(-6, 7, 2)))
print([[str(x), x ** 3] for x in range(4)])

# Multiple values, "if" filters
print([[x, x / 2, x * 2] for x in range(-6, 7, 2) if x > 0])

#  List, Set, Map based on the range
print(set(range(-5, 10, 3)))
print(list(range(-5, 10, 3)))
myMap = {str(x): x ** 3 for x in range(-5, 10, 3)}
print(myMap)

# Generator example: sum of rows
G = (sum(row) for row in matrix)
print(next(G))
print(next(G))
print(next(G))

# Set and Map with function
setSum = {sum(row) for row in matrix}
print(setSum)

# Check existence in 6
if 6 in setSum:
    print(str(6) + " is found")

mapSum = {str(i) : sum(matrix[i]) for i in range(3)}
print(mapSum)

# Nested dictionaries
person = {'name': {'first': 'Bob', 'last': 'Smith'},
          'jobs': ['Developer', 'Cooker'],
          'age' : 36}

print(person)
person['jobs'].append('Sailor')
print(person)

# Check existence in dictionary/map
if 'name' in person:
    print(person['name'])

# Print sorted keys and related values
for key in sorted(person):
    print(key, '=>', person[key])
    
# Clear memory
person.clear()
print(person)


# Tuples - distincts in that they are immutable collections
T = (1, 2, 25, 4, 5)
print(T)
# T[2] = 5  isn't allowed
print(T.index(25))

# Files
dataFile = open('data.txt', 'w')
dataFile.write('Hello\n')
dataFile.write('world\n')
dataFile.close()

dataFile = open('data.txt', 'r')
# Print all the file as a line
print(dataFile.read())
dataFile.close()

for curLine in open('data.txt'): 
    print(curLine)


# Type checking - not "Pythonic"
print(type(matrix),
      type(matrix[0]),
      type(matrix[0][1]) == int,
      isinstance(matrix, list))


list1 = [1, 2, 3]
print(list1[2])

### Sets ###
# Create using set() constructor passing iterable object
mySet = set('Test')
mySet2 = set('Boot')
# Creates set of 1 item of the string 'Set3'
mySet3 = {'Set3'}  

print(mySet.intersection(mySet2))
print(mySet2)

# Can't add List, Add, Dict, because set containts immutable objects, that is hashable
# mySet2.add(['G', 'L'])
# mySet2.add({'GOAL'})

# {1, 2, 3, 4} - {1, 2}
# {1, 2, 3, 4} & {1, 2}
# {1, 2, 3, 4} ^ {1, 2}
# {1, 2, 3, 4} > {1, 2}
# {1, 2, 3, 4} < {1, 2}
# {1, 2} < {1, 2, 3, 4}
# {1, 2} < {1, 2, 3, 4}
# {1, 2, 5} < {1, 2, 3, 4}


L1 = [1, 3, 5]
L2 = L1             # => L2 refers to the same object (only for mutable objects)
L1[0] = 200         # Changes both L2 and L1 (sure)

# Print ID of the objects => equal
print(id(L1), id(L2))

# Make copy
import copy
L2 = copy.copy(L1)      # "shallow" copy
L2 = copy.deepcopy(L1)  # Deep copy with nested structions

# Print ID of the objects => different, anothe object was created
print(id(L1), id(L2))

# or
L2 = list(L1)       # Generage another object using list Constructor 

# Comparisons
L1 == L2            # Compare values
L1 is L2            # Compare identity (the same object or not)

import sys          # Get reference counter for an object
sys.getrefcount(L1)

# Print out list of arguments: sys.argv[0] is the name of the file, as in C
print([x for x in sys.argv])
# Or just
print(sys.argv)

# Comparisons
L1 = [1, 2, 3]
L2 = [1, 2, 3]

# Equal but not the same objects
print(L1 == L2, L1 is L2)

# Equal and the same objects - short strings
S1 = "Test"
S2 = "Test"
print(S1 == S2, S1 is S2)

# Equal and not the same objects - longer strings
S1 = "Long string 444444444444444 666666666666666666666666666666666666"
S2 = "Long string 444444444444444 666666666666666666666666666666666666"
print(S1 == S2, S1 is S2)