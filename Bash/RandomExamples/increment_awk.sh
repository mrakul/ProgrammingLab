#!/bin/bash

input_file="[path_to_file]"

# while read -r line; do
#     if echo "$line" | grep -q -P 'pktlen_[0-9]+'; then
# 	    # product=$(echo $line | grep -ow 'pktlen_') #'^[^$ ]*')
# 	    # old_price=$(echo $line | grep -oP 'pktlen_\K[0-9]*')
#         # new_price=$(expr $old_price + 1)
# 	    a=a+1;
#     else
#         echo "$line"
#     fi
# done < "$input_file"

#!/bin/bash


# awk '/^Number:/ { $2+=1 } { print }' "${input_file}" > tmp.txt
# awk '{ sub(/Number: [0-9]+/, "Number: "$2) } { print }' tmp.txt > "${input_file}"

awk '/pktlen_/ { $3+=1 } { print }' "${input_file}" > tmp.txt

awk '/entropy_/ { $3+=1 } { print }' "tmp.txt" > tmp2.txt
#awk '{ sub(/^ *if \(pktlen_ [0-9]+/, "pktlen"$2) } { print }' tmp.txt > tmp2.txt

# rm tmp.txt
