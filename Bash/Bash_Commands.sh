### find command examples ###

# finds file name recursively with wildcards:
find -name *condition*




### Launch command/executable several times (cycles):
for i in {1..10};
do
    ./C/Concurrency/ConditionVariables/condition_variable.exe;
done;

#In one line to quick copy:
for i in {1..10}; do ./{program.exe}; done;