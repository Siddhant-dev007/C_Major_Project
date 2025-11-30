💱 Exchange Rate Viewer in C
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

An interactive console-based Currency Exchange Rate Analysis System developed in C language, designed to read, display, and analyze historical currency exchange   rate data from CSV files using modular programming and file handling concepts.  


📌 Project Summary
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
This project enables users to view exchange rates for multiple currencies over specified periods, analyse trends between years, and store formatted data in text   files. Built using standard C libraries, it demonstrates efficient CSV parsing, console UI navigation, and modular system design.  

The application supports displaying exchange rates for particular months or years, performing comparative analysis between two-year ranges, and exporting results   for external use.  


✨ Key Features
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

•	Display exchange rates for a selected currency for an entire year  
•	Display rate information for a specific month  
•	Analyse exchange rate trends between two years (min, max, average)  
•	Export rates for all currencies for a given month or year into a formatted .txt file  
•	Read country details from a separate CSV file  
•	Colorized and paginated terminal output for easy readability  
•	Efficient CSV parsing and menu-based navigation  


🧠 Concepts Demonstrated
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Concept	Usage in Project  
•	File Handling (fopen(), fgets(), fprintf(), rewind())             	Reading & writing data       
•	Structures                                                     Storing country information      
•	2D arrays	                                                          CSV column parsing          
•	Functions	                                                           Modular design             
•	String manipulation	                                           Parsing CSV rows and searching    
•	Algorithmic processing	                                           statistical calculations      

🧱 System Architecture & Module Overview
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Main Menu  
 ├── ShowRatesForYear()  
 ├── ShowRatesForMonth()  
 ├── AnalyzeCountryBetweenYears()  
 ├── StoreRatesForAllCountriesInYear()  
 ├── ReadCountries()  
 └── Exit  
 

📂 Directory Structure
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
📦 Exchange-Rate-Viewer  
├── main.c  
├── exchange.c  
├── exchange.h  

👤 Author
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Siddhant Sharma : Sole developer
-
🏁 Conclusion
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
The Exchange Rate Viewer demonstrates practical use of C programming to analyze real financial datasets. By integrating file handling, structured data storage, and   statistical computation, the system offers efficient tools for currency trend analysis and can be extended into financial and banking applications.  


