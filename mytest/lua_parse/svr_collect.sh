#!/bin/bash
if [ $# -ne 1 ]; then
    echo "commond:./run.sh world_id"
    exit 1
fi

world_id=$1

src_name=ct_svrpass.txt
file_name=info_$1.log

if [ -f "$file_name" ]; then
    rm $file_name
fi

#二人模式
play_type=1
for level in {1..10}
do
    let achv_id=$level+32
    actor_info=`awk 'BEGIN{ FS=",";line_cnt = 0;} {if ("'$world_id'"==$1 && "'$play_type'"==$2 && "'$level'"==$3)  {line_cnt+=1; print $8 " " $6 " " $7}} END{print line_cnt}' $src_name`
    base_str="$world_id $play_type $level $achv_id"
    echo $base_str $actor_info >> $file_name
done

#五人模式
play_type=2
for level in {1..10}
do
    let achv_id=$level+42
    actor_info=`awk 'BEGIN{ FS=",";line_cnt = 0;} {if ("'$world_id'"==$1 && "'$play_type'"==$2 && "'$level'"==$3)  {line_cnt+=1; print $8 " " $6 " " $7}} END{print line_cnt}' ct_svrpass.txt`
    base_str="$world_id $play_type $level $achv_id"
    echo $base_str $actor_info >> $file_name
done

#10人模式
play_type=3
for level in {1..5}
do
    let achv_id=$level+52
    let achv_id=$level+42
    actor_info=`awk 'BEGIN{ FS=",";line_cnt = 0;} {if ("'$world_id'"==$1 && "'$play_type'"==$2 && "'$level'"==$3)  {line_cnt+=1; print $8 " " $6 " " $7}} END{print line_cnt}' ct_svrpass.txt`
    base_str="$world_id $play_type $level $achv_id"
    echo $base_str $actor_info >> $file_name
done



