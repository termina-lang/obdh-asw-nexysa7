# TP_0085_ASW_PUS_TC_20_3_TC_20_1_SET_PID_20_TO_66

The test checks that telecommand TC(20,3) to set Parameter 20, of type u8, to
value 66 is executed correctly, and then TC(20,1) retrieves the parameter value
confirming it was set to 66.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (20,3) to set Parameter 20 to 66 | | TC(20,3) | N = 1, Parameter ID = 20, Parameter Value = 66 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (1,7) | | TM(1,1)<br>TM(1,7) | N/A |
| **TO + 5** | **STEP1** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (20,1) to get Parameter 20 value | | TC(20,1) | N = 1, Parameter ID = 20 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (20,2) with Parameter 20 value = 66, and TM (1,7) | | TM(1,1)<br>TM(20,2)<br>TM(1,7) | N = 1, Parameter ID = 20, Parameter Value = 66 |
