### Files basics ###

FILE = './Basics//Files/myFile.txt'

fileToWrite = open(FILE, 'w')

# Write returns the number of written characters
fileToWrite.write("Test string\n")
fileToWrite.write("Test string 2\n")

# Flush the buffer => immediately write to the file, as in C/C++
fileToWrite.flush()

# Print all the file as a string
open(FILE).read()               # Read all at once into string
print(open(FILE).read())        # User-friendly display

# Print file line by line
for line in open(FILE):
    print(line, end='')         # end='' => print nothing instead of NewLine as default
    
fileToWrite.close()

BIN_FILE ='./Basics/Files/binFile.txt'

binFile = open(BIN_FILE, 'wb')
binFile.write(b'\x00\x00\x00\x07spam\x37\x00\x08')  # Write only as a special byte-string
# Write data
binFile.close()

binFile = open(BIN_FILE, 'rb')
data = open(BIN_FILE, 'rb').read()              # => <class '_io.BufferedReader'>
# type(open(FILE, 'r').read())                  # => <class '_io.TextIOWrapper'>

print(data)
print(type(data))

print(data[4:8])
print(hex(data[4:8][0]))                             # returns integer, ASCII representation
print(hex(data[4:9][4]))                             # returns integer, ASCII representation
print(chr(data[4:9][4]))                             # char

binFile.close()

# Different types
DIFF_TYPES_FILE = './Basics/Files/diffTypes.txt'

# Data to write
X, Y, Z = 43, 44, 45
S = 'Spam'
D = {'a': 1, 'b': 2}
L = [1, 2, 3]

F = open(DIFF_TYPES_FILE, 'w')
F.write(S + '\n')
F.write('%s,%s,%s\n' % (X, Y, Z))
F.write(str(L) + '$' + str(D) + '\n')
F.close()

# diffTypesFile = open('./Basics/diffTypes.txt', 'w')
# diffTypesFile.write(r"Spam\n43,44,45\n[1, 2, 3]${'a': 1, 'b': 2}\n")
# diffTypesFile.close()


# Read from the file
fileDiffTypes = open('./Basics/Files/diffTypes.txt', 'r')
fullFile = fileDiffTypes.read()

# Print all the file
print(fullFile)                                 # NewLines are processed
print(repr(fullFile))                           # NewLines are in the string

# Print as separate lines
fileDiffTypes.seek(0)
linesOfFile = fileDiffTypes.readlines()
print(linesOfFile)                              # Strings contains NewLines
print(repr(linesOfFile))                        # Strings contains NewLines

# Split explicitly using .split() method
fileDiffTypes.seek(0)
fullFile = fileDiffTypes.read()
print(linesOfFile)

linesOfFile = fullFile.split()                     # Makes the same internally (?), but not incliude NewLine (!)
print(linesOfFile)              

linesOfFile = fullFile.split('\n', maxsplit = 1)   # Make split until finding one separator (the rest is not splitted)
print(linesOfFile)              
print(fullFile.rsplit('\n', maxsplit = 1))         # Find delimiter from the right

# Or create three partitions: 
print(fullFile.partition('\n'))                    # Creates three partitions as a typle(str, str, str): left side, separator itself, right side
print(fullFile.rpartition('\n'))                   # The same from the right side

for curStr in fullFile.split('\n'):                # After splitting, the strings don't contain NewLines, no need to rstrip
    print(curStr)        
    print(repr(curStr))        
    print(curStr.rstrip())                         # Remove whitespace from the end (no need after splitting)

# Print numbers of the [1] element
print("Print numbers: ", [int(curNum) for curNum in fullFile.split('\n')[1].split(',')])

# eval() built-in function: recognizes and returns object of its type
print("Print list of objects: ", [eval(curStr) for curStr in fullFile.split('\n')[2].split('$')])
# Note: eval() is too general and can execute text as a command, so it can be harmful if not trusted source of the input

fileDiffTypes.close()


### pickle module, serializing objects ###
import pickle
PICKLE_FILE = './Basics/Files/pickles.pkl'

# Write binary "pickled" data from the file
pickleFile = open(PICKLE_FILE, 'wb')           # Open as a binary to write

pickle.dump({'1' : "First string", '2' : "Second string"}, pickleFile)
pickle.dump(35, pickleFile)
pickle.dump({'3' : "Third string", '4' : "Fourth string"}, pickleFile)

pickleFile.close()

# Read binary "pickled" data from the file
pickleFile = open(PICKLE_FILE, 'rb')

# TODO: load in a cycle (?)
print(pickle.load(pickleFile))
print(pickle.load(pickleFile))
print(pickle.load(pickleFile))

# Note: pickle must be faster, but unsafe

### JSON format ###
import json
person = dict(first = 'Lane', last = 'Train')
recPerson = dict(name = person, job = ['dev', 'mgr'], age = 40.5)

# Serialize object in a string JSON format
personToJSON = json.dumps(person)
print("Person JSON: ", personToJSON, ", type of personToJSON", type(personToJSON))

# Deserialize object
personFromJSON = json.loads(personToJSON)
print("Person JSON: ", personFromJSON, ", type of personFromJSON", type(personFromJSON))

# Write JSON to a file
JSON_FILE = './Basics/Files/JSON_objects.txt'
PERSONS_FILE = './Basics/Files/JSON_persons.txt'

fileJSON = open(JSON_FILE, 'w')                   # Open as a text file to write-append

# Write a JSON object
json.dump(recPerson, fileJSON, indent = 4)        # Additionally specify indent value of each level
fileJSON.write('\n')        

# JSON must contain one object with high-level {} scope
# If several objects, it can be represented as JSON Lines format text file
# json.dump(str(250), fileJSON, indent = '')
# fileJSON.write(',\n')        

# json.dump({"Key" : "Value related to the key"}, fileJSON, indent = 4)
# fileJSON.write(',\n')       

fileJSON.close()

# Read written object
fromJSONString = json.load(open(JSON_FILE))
print(fromJSONString)
print("Person == Person from JSON:", recPerson == fromJSONString)

# Read separate persons file
personsJSON = json.load(open(PERSONS_FILE))
print(personsJSON)


### csv file format ###
import csv
CSV_FILE = './Basics/Files/cars.csv'

readerCSV = csv.reader(open(CSV_FILE))

# Read a row as a list of values
for row in readerCSV:
    print(type(row), ": ", row)
    
    
### Packed structures in binary files ###
import struct

BINARY_FILE = './Basics/Files/binary_data.csv'
binFile = open(BINARY_FILE, 'wb')

# Pack data to a struct
data = struct.pack('>i4sh', 7, b'spam', 8)
print(data)

# Write to a file
binFile.write(data)
binFile.close()

# Open binary output file
# Make packed binary data
# Write byte string
binFileRead = open(BINARY_FILE, 'rb')
# Read all the file
data = binFileRead.read()
print(data)

unpackedData = struct.unpack('>i4sh', data)
print(unpackedData)

binFileRead.close()

### Use Context Manager syntax ###
with open(PERSONS_FILE) as fileToRead:
    try:
        for line in fileToRead:
            print(line, end = '')
    finally:
        fileToRead.close()

print("End of the program")