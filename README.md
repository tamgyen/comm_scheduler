# comm_scheduler
Communication scheduler demo for an embedded system

2.1. TESTING THE PROTOCOL
I first implemented the fieldObject as a separate file as suggested. Then I created another source file env.c for the controlObject environment and the scheduler. The scheludel is just a sequential setting of the object parameters (timers and io messages) and the calling of the field and control objects. It starts with an initialization and reset of the parameters, then a handshake is done, lastly the communication is established. The messages are printed to the console, as well as to the messagelog.txt file. The two source files were successfully compiled together to testcomm.exe using Cygwin64.
2.2. MEASURING BRANCH COVERAGE 
3.I created the driver.c to create suite for testing all the transitions in the fieldObject. In every test case first, the variables are reset and then set specifically to reach all branches. I extended the output messages of the fieldObject and logged the output in the driver after executing each branch in a for loop. Then I compiled the driver and the fieldObject together, executed the created model.exe, and run gcov (see figure1). The files can be found in the bcoverage folder. The branch coverage is 100%.
