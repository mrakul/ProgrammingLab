import re

# Get features from the trees

fileToRead = open('./Basics/RegExp/trees.txt', 'r')
fileToWrite = open('./Basics/RegExp/tree_features.txt', 'w')

treesData = fileToRead.readlines()

featuresSet = set()

for curLine in treesData:
    match = re.search(r'row\[\'(.*)\'\]', curLine)
    
    if match:
        featuresSet.add(match.group(1))
        
for curFeature in featuresSet:
    print(curFeature)
    fileToWrite.write(curFeature)
    fileToWrite.write(', ')
    
fileToRead.close()
fileToWrite.close()
    
# Get features from the trees
    
fileToRead = open('./Basics/RegExp/function.txt', 'r')
fileToWrite = open('./Basics/RegExp/function_features.txt', 'w')

treesData = fileToRead.readlines()

featuresSet = set()

for curLine in treesData:
    # Returns a list of matched substrings, comparing to re.match(), which returns the first occurence
    matchedList = re.findall(r'[a-z_]+\d{0,2}[a-z_]+\d', curLine)
    
for curFeature in matchedList:
    featuresSet.add(curFeature)
        
for curFeature in featuresSet:
    print(curFeature)
    fileToWrite.write(curFeature)
    fileToWrite.write(', ')
    
fileToRead.close()
fileToWrite.close()


