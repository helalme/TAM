### Background:
There are so many plants and engineering use cases where assessing thermal fatige is crucial to indenify lifetime of a component. Thermal fatigue is usually observed where themperature fluctuates regularly or irreguraly. For correct assessement of lifetime, we need to know accurate temperature history of the component. For instance, cooling system is a vital part of nuclear power plant compoments, where outside temperature of a cooling compoent (e.g. pipe) can be measured using sensors, however, inner-wall temperature of that component cannot be accessed. In such cases, it is necessary to correctly evaluate the temperature history of the inner-wall of the component experiencing thermal fluctuation.

Thermal conduction from hot side to colder side is a common phenomena, let's say a FORWARD heat conduction problem (FHCP), and it can be easily simulated. However, assessing thermal fluctuation history from colder side to hotter side is a severely ill-posed problem and knows as inverse heat conduction problem (IHCP). Mathematical optimization approaches can be applied to solve a 3D IHCP with significant computational complexity. There is always high uncertainly in the solution due to non-uniqueness and high noise. In this case, any other techniques (like an algorithm) giving the reasonable solution is highly important. 

### Algorithms for FHCP and IHCP:


This software kit can be used for solving 3D inverse heat conduction problems.
Test examples are used for 2D pipe case. Both forware and inverse problems can be solved.


How to Use:
  1. Go to TAM>Debug>TAM.exe,    an interactive window will pop up showing the target directory
  2. Close the UI window  
  3. Put all input files into the target directory, shown at the beginning of the window.
  4. Rerun the program. It will show each .txt file with a number.
  5. select forward or inverse by entering corresponding number.
  6. It will ask for two input data files, reference data and inner temperature data for Forward problems
	and outerTemp data for inverse problems.
  7. The program will generate a message when result file is generated. 



