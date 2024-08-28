# Get number of sessions with decision and total number of sessions
file_prefix="$1";

# Redirect output once
exec >> "report.txt";
echo -e "======================================================================================================";
echo -e "Pcap processed: \t\t\t$1.pcap";

# All sessions
all_sess_cnt=$(cat $file_prefix"_all_sessions.txt" | wc -l);
echo -e "Total number of sessions: \t$all_sess_cnt";

# Sessions having decision
decision_sess_cnt=$(cat $file_prefix"_decision_made.txt" | wc -l);
echo -e "Sessions with decision: \t$decision_sess_cnt";

# Sessions with "some_sign"s
matched_sess_cnt=$(grep "some_sign" $file_prefix"_decision_made.txt" | wc -l);
echo -e "SomeSign matched: \t\t$matched_sess_cnt";

# Matched ratio: matched sessions counter / having decision session counter
matched_ratio=$((matched_sess_cnt/decision_sess_cnt));

#echo -e "$matched_ratio";
matched_ratio=$(echo "scale=2; $matched_sess_cnt / $decision_sess_cnt" | bc);
echo -e "Matched ratio: \t\t\t\t0$matched_ratio";
