# A first Python script
import sys

# String examples>>> line = 'aaa,bbb,ccccc,dd'
string = 'a\nb\tc'
print(string)

# Output
print(f"Length of string {string} is: %s" % len(string))
print(f"Length of string {string} is: {0}".format(len(string)))

# Multiline strings
mantra = """Always look
           on the bright
           side of life."""

print(mantra)

string = "Test"\
         "Test2"

print(string)
print (string * 2)

# .join() method: returns a new string
A = 'Test string'
A.join(' and more symbols')
print(A)

# Third limits = 'abcdefghijklmnop'
S = 'abcdefghijklmnop'

print(S[1:10:2])
print(S[::2])
print(S[::-1])      # Revert the string

# str() vs repr()
print("str:", str('spam'), ',', "repr:", repr('spam'))

# Char to binary code and binary code to char
print(ord('s'))
print(chr(115))

# Bit to int and opposite
print(int('1101', 2))      # Specify the number system as the second operand
print(bin(13))

# Print out required number of bits
number = 17
print(f"Binary representation of {number}: {bin(number)}")
print("Required number of bits: ", number.bit_length())
print("Number of bits set: ", number.bit_count())

# Print table of bits set in the byte
for num in range(0, 256):
        print(num.bit_count(), end=' ')
        
        if (((num + 1) % 16) == 0):
                print('\n', end='')             

# Changing string
S = 'splot'
# S[0] = 'l'    => Restricted, strings are immutble
S = S.replace('pl', 'pamal')    # Need to create a new one

L = list(S)     # => modifying works for lists
L[0] = 'q'
S = ''.join(L)  # => convert back


### Parsing ###
line = 'aaa bbb ccc'
words = line.split()    # Returns list of words
words

line = 'train,bane,flame'
words = line.split(',')

# More methods
line = "The line contains newline!\n"
line.rstrip()
line.upper()
line.isalpha()
line.endswith('\n')
line.startswith('The')

# Output approaches
myInt = 15
"I want to output integer: %d" % myInt
"I want to output string: %s" % "\'String to output\n"
"I want to output hex: {0} ".format(hex(myInt))
f"Print integer: {myInt}"

# Every object can be converted to string, so no need to conver it explicitly when output
"%s, %s, %s" % (42, 3.14159, [1, 2, 3])

# Dictionary formatted output
values = {'name': 'Bob', 'age': 40}

# Output 'name' as a string, age as a string
reply = """
        Greetings...
        Hello %(name)s!
        Your age is %(age)s
"""
print(reply % values)

template = '{0}, {1} and {2}'
template.format('spam', 'ham', 'eggs')
template = '{motto}, {pork} and {food}'
template.format(motto='spam', pork='ham', food='eggs')
template = '{motto}, {0} and {food}'
template.format('ham', motto='spam', food='eggs')
template = '{}, {} and {}'
template.format('spam', 'ham', 'eggs')
# Same via expression
template = '%s, %s and %s'
template % ('spam', 'ham', 'eggs')
template = '%(motto)s, %(pork)s and %(food)s'
template % dict(motto='spam', pork='ham', food='eggs')

print('Test')