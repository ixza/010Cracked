# 010Cracked
License bypass patcher for 010Editor v12.0.1.0 \n
It should accept any password on the license check screen.


<b>Doing it manually</b>
1. go to 010Editor.exe+1F5595 offset. It should be cmp edi,000000DB
2. change the instruction "81 FF DB000000" to NoOp "90 90 90909090" 
