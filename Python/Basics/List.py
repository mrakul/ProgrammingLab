# List basics

list1 = [1, 2, 3]
list2 = list1 + [6, 9]

# Add to the end of the list and pop out of the list
list1.append([2, 4, 5])
list1.pop()     # => end of the list serves as the head of the stack

# Sort, revert
list1 = [1, 2, 3, [5, 9], 10]
# list1.sort()  # => can't be called, since different object types

list1[3] = 200
list1.reverse()

# Using for to create list
repetitions = [c * 4 for c in 'SPAM']
repetitions[2:4] = ['new', 'new']

# Deletion/Insertion using slices
L = [1, 2, 3]
L[1:2] = [4, 5]     # Replacement/insertion
L[1:1] = [6, 7]     # Insertion (replace nothing)
L[1:2] = []         # Deletion (insert nothing), remove second item

L.pop(1)
L.insert(1, '250000')



L
