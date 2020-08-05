### Background:
There are so many plants and engineering use cases where assessing thermal fatige is crucial to indenify lifetime of a component. Thermal fatigue is usually observed where themperature fluctuates regularly or irreguraly. For correct assessement of lifetime, we need to know accurate temperature history of the component. For instance, cooling system is a vital part of nuclear power plant compoments, where outside temperature of a cooling compoent (e.g. pipe) can be measured using sensors, however, inner-wall temperature of that component cannot be accessed. In such cases, it is necessary to correctly evaluate the temperature history of the inner-wall of the component experiencing thermal fluctuation.

Thermal conduction from hot side to colder side is a common phenomena, let's say a FORWARD heat conduction problem (FHCP), and it can be easily simulated. However, assessing thermal fluctuation history from colder side to hotter side is a severely ill-posed problem and knows as INVERSE heat conduction problem (IHCP). Mathematical optimization approaches can be applied to solve a 3D IHCP with significant computational complexity. There exists high uncertainly always in the solution due to non-uniqueness and unstability (high noise). In this case, any other techniques (like an algorithm) giving the reasonable solution is highly important. 

### Algorithms for FHCP and IHCP:
The mathematical formulation of the developed 3D FHCP and IHCP has been presented in the original research work, and the related chapter is given in the PDF file.

### TAM Console App:
Following the two above algorithms a console application, TAM - Thermal Analysis Mosule, was developed in C++. The development was done in early 2013, that's why modern syntax and semantics of C++11/14/17/20 were not applied. The basic idea is, we need some **reference temperature** that can be computed by simulating simple heat conduction problem using any commercial/open-source software. As usually, we need outer surface (colder) temperature history for IHCP and inner surface (Hotter) temperature history for FHCP. The app TAM has been extensively tested with 2D forware/inverse problems data, even though the algorithms and software is developed for 3D problems.

### How to Use:
Both forware and inverse problems can be solved using TAM. All codes are presented in TAM folder. To get binaries, or executable, simply build the solution in Visual Studio. Alternatively, if you are interested about the app/binaries, please send a request to helalme@yahoo.com.

Temperature history is to be placed in the *data* folder, output file will be generated in the *output* folder. If you start the app by double clicking TAM.exe, the user interface will show all files available in the *data* folder, along with assigning a number for each file. At first, UI will ask the user the problem type is to be solved, i.e. forward or inverse type. 

#### Example:
For both types of problems, first we need to fix number of points we want to consider over a surface. For example, a pipe-cross-section can be considered a 2D problem, where only half of the X-section will be sufficient for the forward/inverse problems due to symmetry. So we can consider any the number of points (e.g. 2, 4, 6, 8 etc.) over inner and ourter surfaces. In the data folder, four data sets have been provided. 

Consider a 2D pipe problem, where number of points are 18 (lets say 18 sensors are placed over the outerwall). So we will have a temperature history of 18 points. We also need *reference temperature* file. Using these two files (outer wall temperature history and reference temperature) we can solve IHCP to know the temperature history of inner wall. Similarly, for FHCP, we need reference temperature an inner wall temperature history.

Two example screen shots of the UI has been given in the **UI.pdf** file. This 2D pipe problem considers 18 points, and temperature history of 500 seconds. Once the computation is done with forward or inverse problem, the program will generate a message. Phease have a look at UI.pdf file.  



