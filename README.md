# combination-of-dishes-to-meet-target-price

Program which will process the data listed below. 
Input must be a csv file and data is read from it. 

**Input constraints:**
  1. The first variable is the target price and the following data values are menu items you could buy. 
  2. The program will then find a combination of dishes that has a total of exactly the target price. 
  3. If there is no solution if found, then the program will print that there is no combination of dishes that is equal to the target price. 
  4. The program can run with different data files

**Instructions on how to run the program from command line:**    
    
    'g++ -std=c++11 combinationOfDishes.cpp -o combinationOfDishes'   
    './combinationOfDishes input_file.csv'    
     
    
Here are some sample data values: 

'Target price, $30.10'    
'                     '    
'mixed fruit,$2.15'        
'french fries,$2.75 '       
'side salad,$3.35'        
'hot wings,$3.55'      
'mozzarella sticks,$4.20'        
'sampler plate,$5.80'        
