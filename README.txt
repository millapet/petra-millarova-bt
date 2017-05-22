Please ensure you have boost libraries installed. 

FOR SGF
Use SGF to load, parse and smooth data from the desired folder 
and save them to the folder of your choice. 
M is the length of the filter (For MA, SGF and derivatives)
N is the polynomial used (for derivatives and SGF)
S is the derivative order (for computing derivatives)

To correctly execute the program, 
enter the following information in this order (separated with a space):
[input file path] [output folder] [filter type] [filter configuration]

Filter types: 
SGF (Savitzky-Golay Filter)
MA (moving average filter)
der (derivatives using the SGF)

Filter configuration:
for SGF enter M (filter half-width) and N (polynomial order) separated by a dash only (-)
for MA filter enter only M
for der enter M-N-S, where S is the derivative order you are willing to use

If you are willing to process more than just one file, the usage of *.bat files is reccomended.
Hope everything runs smoothly!