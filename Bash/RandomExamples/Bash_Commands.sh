### find command examples ###

# finds file name recursively with wildcards:
find -name *condition*

# cd to the directory name of the found file (-f flag) with the name {filename}
cd "$(dirname "$(find -type f -name {filename} | head -1)")"


### Launch command/executable several times (cycles):
for i in {1..10};
do
    ./C/Concurrency/ConditionVariables/condition_variable.exe;
done;

#In one line to quick copy:
for i in {1..10}; do ./{program.exe}; done;