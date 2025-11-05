/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:02 by uxmancis          #+#    #+#             */
/*   Updated: 2025/11/05 12:57:32 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* yearMonthExistsInDB
*
*   The function tell us whether if there is a line that meets the following criteria:
*       1) Same YEAR as dateInput
*       2) Same MONTH as dateInput
*       3) Lower DAY than dateInput => we can use it :)
*
*   Returns:
*       true: YES YYYY-MM was found
*       false: NO YYYY-MM was NOT found
*
*/
bool yearMonthExistsInDB (std::ifstream &dbFile, std::string dateInput)
{
    /* Makes sure we start to read file from the beginning */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    /* Original dateInput: */
    unsigned int yrInput = atoi(dateInput.substr(0,4).c_str());
    unsigned int moInput = atoi(dateInput.substr(5,2).c_str());
    unsigned int dayInput = atoi(dateInput.substr(8,2).c_str());;
    // std::cout << CYAN "[INPUTDATE]" RESET_COLOUR " yrDB = " << yrInput << ", mo = " << moInput << ", dayDB = " << dayInput << std::endl;

    
    std::string dbLine;
    std::string closestDbLine;
    unsigned int yrDB;
    unsigned int moDB;
    unsigned int dayDB;
    
    /* We make sure we start to read file from the beginning */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */
    // unsigned int dayClosest = dayInput;
    while(getline(dbFile, dbLine))
    {
        /* Get date from DB */
        yrDB = atoi(dbLine.substr(0,4).c_str());
        moDB = atoi(dbLine.substr(5,2).c_str());
        dayDB = atoi(dbLine.substr(8,2).c_str());

        if (yrDB == yrInput && moDB == moInput && dayDB < dayInput)
            return (true);
    }
    return (false); /* year-month NOT found in DB */

}


/* getClosestDateSameMoth
*
*   We call getClosestDateSameMonth when we already now that YES there IS some line in DB 
*   that meets criteria predefined in yearMonthExistsInDB.
*
*   Returns: 
*       dbLine: when Successful
*       NOT_FOUND: when failure
*
*/
std::string getClosestDateSameMonth (std::ifstream &dbFile, std::string dateInput)
{
    // std::cout << YELLOW "Case A | dateInput = " << dateInput << RESET_COLOUR << std::endl;

    /* Original dateInput: */
    unsigned int dayInput = atoi(dateInput.substr(8,2).c_str());; /* we'll use it as a reference */
    (void) dayInput;

    /* We'll go find day [0 - dayInput] in already defined month and year */
    unsigned reference_yr = atoi(dateInput.substr(0,4).c_str());
    unsigned reference_mo = atoi(dateInput.substr(5,2).c_str());
    unsigned reference_day = atoi(dateInput.substr(8,2).c_str());
    // std::cout << PINK << "Reference = " << reference_yr << "-" << reference_mo << "-" << reference_day << RESET_COLOUR << std::endl;

    std::string dbLine;
    unsigned int yrDB;
    unsigned int moDB;
    unsigned int dayDB;
    unsigned int closestDay = reference_day - 1;
    // std::cout << "Init closestDay = " << closestDay << std::endl;
    /* Let's go verify which is the first number we find getting lower from dayInput, it will iterate n times. N = possibilities [0-dayInput]*/
    /* Each possibility = check whole file */
    /* In order inner conditional to match, closestDay already defined as framework so that firs time conditional matches that's the line we wanna get :) */
    /* Makes sure we start to read file from the beginning */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */
    
    while (closestDay > 0)
    {
        // int i = 0;
        while(getline(dbFile, dbLine)) /* Reads 100% DB. Once condition matches, returns dbLine.*/
        {
            /* Get date from DB */
            yrDB = atoi(dbLine.substr(0,4).c_str());
            moDB = atoi(dbLine.substr(5,2).c_str());
            dayDB = atoi(dbLine.substr(8,2).c_str());
            // std::cout << "-> Checking DB line: " << dbLine << " | yrDB = " << yrDB << ", moDB = " << moDB << ", dayDB = " << dayDB << std::endl;

            /* C*/
            if (yrDB == reference_yr && moDB == reference_mo && dayDB == closestDay)
            {
                // std::cout << GREEN "[MATCH FOUND] " RESET_COLOUR << std::endl;
                return (dbLine);
            }
            // if (i == 10)
            //     break;
            // i++;
        }
        /* So that we can start read again from the beginning of the file :)*/
        dbFile.clear();
        dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */
        
        closestDay--;
    }
    return ("NOT_FOUND");
}

/* isLineSameYear
*
*   Checks whether if there is any line in data.csv that matches the following
*   criteria:
*       1) SAME year as dateInput
*       2) SAME or EARLIER month as dateInput
*/
bool isLineSameYear (std::ifstream &dbFile, std::string dateInput)
{
    unsigned reference_yr = atoi(dateInput.substr(0,4).c_str());
    unsigned reference_mo = atoi(dateInput.substr(5,2).c_str());
    // std::cout << CYAN "RefYr = " << reference_yr << ", RefMo = " << reference_mo << RESET_COLOUR << std::endl;

    std::string dbLine;
    unsigned yrDB;
    unsigned moDB;

    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */
    
    while(getline(dbFile, dbLine))
    {
        /* Get date from DB */
        yrDB = atoi(dbLine.substr(0,4).c_str());
        moDB = atoi(dbLine.substr(5,2).c_str());
        
        // std :: cout << YELLOW << "yrDB = " << yrDB << ", moDB = " << moDB << RESET_COLOUR << std::endl;
        if (yrDB == reference_yr && moDB <= reference_mo)
            return (true);
    }
    return (false);
}

unsigned int getChosenYear(std::ifstream &dbFile, std::string dateInput)
{
    unsigned int chosenYear = atoi(dateInput.substr(0,4).c_str()) - 1; /* Set to max possible */
    // std::cout << YELLOW "chosenYear = " << chosenYear << RESET_COLOUR << std::endl;

    std::string dbLine;
    unsigned int yrDB;
    bool found = false;

    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    /* Objective of the loop: to choose the closest year :) */
    int it = 50;
    while (chosenYear > 0 && !found)
    {
        // std::cout << PINK << "chosenYear = " << chosenYear << std::endl;
        /* ... will be compared with 100% lines of DB.*/
        while (getline(dbFile, dbLine) && it > 0)
        {
            // std::cout << YELLOW "dbLine = " << dbLine << RESET_COLOUR << std::endl;
            /* Get dateInput */
            yrDB = atoi(dbLine.substr(0,4).c_str());
            // std::cout << CYAN << "yrDB = " << yrDB << RESET_COLOUR << std::endl;
            
            if (yrDB == chosenYear)/* Once the 1st time this is found ==> the highest year has been found! This is it! :) )*/
            {
                // std::cout << CYAN "yrDB = " << yrDB << ", chosenYear = " << chosenYear << RESET_COLOUR << std::endl;
                found = true;
                break;
            }
            // else
                // std::cout << RED "DOES NOT MATCH" RESET_COLOUR << std::endl;

        }
        if (!found)
            chosenYear--;
    }
    /* Chosen year: */
    // std::cout << "chosenYear = " << chosenYear << std::endl;
    // chosenYear = atoi(dbLine.substr(0,4).c_str());
    // std::cout << "/// chosenYear = " << chosenYear << std::endl;
    return (chosenYear);
}

unsigned int getChosenMonth(std::ifstream &dbFile, std::string dateInput, unsigned int chosenYear)
{
    bool found;
    std::string dbLine;
    unsigned int yrDB;
    unsigned int moDB;
    
    /* The chosenYear is already diff from dateInput. Then, month can be any, literally [0-12]. We'll choose the latest :) */
    /* Objective of the loop: to chooseMonth */
    unsigned int refMo = atoi(dateInput.substr(5,2).c_str());
    // std::cout << "refMo = " << refMo << std::endl;
    unsigned int chosenMonth = 12;
    found = false;

    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */
    int i = 10;
    while (chosenMonth > 0 && !found)
    {
        while(getline(dbFile, dbLine)  && i > 0 ) /* i is temp, later should be erased from all loops */
        {
            /* Get dateInput */
            yrDB = atoi(dbLine.substr(0,4).c_str());
            moDB = atoi(dbLine.substr(5,2).c_str());

            // std::cout << "yrDB = " << yrDB << ", moDB = " << moDB << "| chosenYr = " << chosenYear << ", refMo = " << refMo << ", chosenMonth (it) = "<<  chosenMonth << std::endl;
            if (yrDB == chosenYear /*&& moDB == chosenMonth*/ && moDB < refMo)
            {
                found = true;
                break;
            }
            i--;
        }
        if (!found)
            chosenMonth--;
    }
    /* Chosen month: */
    chosenMonth = atoi(dbLine.substr(5,2).c_str());
    // std::cout << "///chosenMonth = " << chosenMonth << std::endl;
    
    return (chosenMonth);
}

unsigned int getChosenDay(std::ifstream &dbFile, unsigned int chosenYear, unsigned int chosenMonth)
{
    bool found = false;
    std::string dbLine;
    unsigned int yrDB;
    unsigned int moDB;
    unsigned int dayDB;
    
    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    /* YEAR and MONTH are already chosen. Finally, let's choose the latest DAY :),  lit can be [0-31] :) */
    unsigned int chosenDay = 31;
    while (chosenDay > 0 && !found)
    {
        /* We make sure we can read again the file */
        dbFile.clear();
        dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

        while (getline(dbFile, dbLine)/* && i > 0*/ )
        {
            /* Get dateInput */
            yrDB = atoi(dbLine.substr(0,4).c_str());
            moDB = atoi(dbLine.substr(5,2).c_str());
            dayDB = atoi(dbLine.substr(8,2).c_str());

            if (yrDB == chosenYear && moDB == chosenMonth && dayDB == chosenDay)
            {
                found = true;
                break;
            }
                
        }
        if (!found)
        {
            chosenDay--;
        }
    }
    return (chosenDay);
}


/* Case C:
*
*   YEAR: Different from dateInput --> It must be min. -1 than dateInput. Assigned in definition.
*                                      In the 1st loop, we iterate descending (from the highest 
*                                      possible to the lowest possible.
*
*   MONTH: It can be any month, as YEAR is already different.
*/
std::string getClosestDate_diffYear (std::ifstream &dbFile, std::string dateInput)
{
    (void) dbFile;
    (void) dateInput;

    std::string dbLine;
    
    unsigned int yrDB;
    unsigned int moDB;
    unsigned int dayDB;

    // bool found = false;

    /* chosenYear is defined */
    unsigned int chosenYear = getChosenYear(dbFile, dateInput);
    // std::cout << "/// chosenYear = " << chosenYear << std::endl;

    /* chosenMonth is defined*/
    unsigned int chosenMonth = getChosenMonth(dbFile, dateInput, chosenYear);
    // std::cout << "///chosenMonth = " << chosenMonth << std::endl;

    /* chosenDay is defined*/
    unsigned int chosenDay = getChosenDay(dbFile, chosenYear, chosenMonth);
    // std::cout << "///chosenDay = " << chosenDay << std::endl;

    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    while (getline(dbFile, dbLine))
    {
        /* Get dateInput */
        yrDB = atoi(dbLine.substr(0,4).c_str());
        moDB = atoi(dbLine.substr(5,2).c_str());
        dayDB = atoi(dbLine.substr(8,2).c_str());
        if (yrDB == chosenYear && moDB == chosenMonth && dayDB == chosenDay)
            break;
    }

    // std::cout << YELLOW "/////////////// dbLine = " << dbLine << std::endl;
    return (dbLine);
}

std::string getClosestDate_diffMonth(std::ifstream &dbFile, std::string dateInput)
{

    unsigned int yrDB;
    unsigned int moDB;
    unsigned int dayDB;

    // std::cout << "dateInput = " << dateInput << std::endl;

    /* Year is already decided */
    unsigned int chosenYear = atoi(dateInput.substr(0,10).c_str());
    // std::cout << CYAN "✅chosenYear = " << chosenYear << RESET_COLOUR << std::endl;
    
    /* chosenMonth is defined*/
    unsigned int chosenMonth = getChosenMonth(dbFile, dateInput, chosenYear);
    // std::cout << "✅chosenMonth = " << chosenMonth << std::endl;

    /* chosenDay is defined*/
    unsigned int chosenDay = getChosenDay(dbFile, chosenYear, chosenMonth);
    // std::cout << "✅chosenDay = " << chosenDay << std::endl;

    /* We make sure we can read again the file */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    std::string dbLine;
    while (getline(dbFile, dbLine))
    {
        /* Get dateInput */
        yrDB = atoi(dbLine.substr(0,4).c_str());
        moDB = atoi(dbLine.substr(5,2).c_str());
        dayDB = atoi(dbLine.substr(8,2).c_str());
        if (yrDB == chosenYear && moDB == chosenMonth && dayDB == chosenDay)
        {
            // std::cout << GREEN "[MATCH FOUND ]" RESET_COLOUR << std::endl;
            break;
        }
            
    }

    // (void) dbFile;
    // (void) dateInput;
    return (dbLine);
}

/* Gets lower date which is the closest */
std::string getClosestValue(std::ifstream &dbFile, std::string dateInput)
{
    // std::cout << PINK "---------------------------getClosestValue --------------------------- " RESET_COLOUR << std::endl;
    // std::cout << PINK "*THERE WAS NO EXACT MATCH FOR DATE, LET'S FIND CLOSEST DATE POSSIBLE!*" RESET_COLOUR << std::endl;
    // std::string dbLine = yearMonthExistsInDB(dbFile, dateInput);
    std::string dbLine = "";

    // std::cout << PINK "👀 dateInput = " << dateInput << RESET_COLOUR << std::endl;

    /* DONE It works! */
    if (yearMonthExistsInDB(dbFile, dateInput)) /* Yes there is sameYYYY-sameMM-LowerDay*/
    {
        // std::cout << PINK "CASE A --> Same YEAR and MONTH" RESET_COLOUR << std::endl;
        dbLine = getClosestDateSameMonth(dbFile, dateInput); /* Which one is it? */
    }
    else if (isLineSameYear(dbFile, dateInput)) /* Yes there is sameYYYY*/
    {
        // std::cout << PINK "CASE B --> Same YEAR" RESET_COLOUR << std::endl;
        // dbLine = /* Which one is it? */
        dbLine = getClosestDate_diffMonth(dbFile, dateInput);
    }
    else /* There is NO line same year */
    {
        // std::cout << PINK "CASE C --> DIFFERENT YEAR " RESET_COLOUR  << std::endl;
        dbLine = getClosestDate_diffYear(dbFile, dateInput);
    }

    // std::cout << PINK "[COMPLETED] ---------------------------------------------------------- " RESET_COLOUR<< std::endl;
    return (dbLine);
}

/* getValueInDate
*
*   Gets the bitcoin value for a specific date.
*
*   Returns:
*       bitcoinValueInDate
*
*   The result of this function is used in getTotalValue function.
*/
float getValueInDate (std::string line)
{    
    /* Generate dateInput */
    std::string dateInput = line.substr(0,10).c_str();
    
    /* Open data.csv file */
    std::ifstream dbFile("data.csv");
    if (!dbFile.is_open()) /* Should never happen */
    {
        std::cerr << "Error: could not open file" << std::endl;
    }

    std::string dbLine; /* database where to find */
    float bitcoinValueInDate = -1;

    /* Option 1: Exact date is found. Reads 100% DB. */
    while(getline(dbFile, dbLine))
    {
        if (dbLine.substr(0,10).c_str() == dateInput) /* Yes this is the exact day! */
            bitcoinValueInDate = atof(dbLine.substr(11).c_str());
    }
    
    /* To be able to read it from the beginning */
    dbFile.clear();
    dbFile.seekg(0, std::ios::beg); /* Moves the poointer to the beginning */

    if (bitcoinValueInDate != -1)
    {
        // std::cout << GREEN << "✅ Exact date found: " << dateInput << RESET_COLOUR << std::endl;
        // std::cout << "bitcoinValueInDate = " << bitcoinValueInDate << std::endl;
    }
    else /* Option #2: find the closest date. When bitcoinValueInDate still == -1, means it didn't find the exact date. Let's find the closest! :) */
    {
        // std::cout << RED << "❌ Date not found" RESET_COLOUR << std::endl;
        dbLine = getClosestValue(dbFile, dateInput);

        /* this print is not working properly */
        // std::cout << YELLOW << "dbLine = " << dbLine << RESET_COLOUR  << std::endl;
        bitcoinValueInDate = atof(dbLine.substr(11).c_str());
    }
    
    return (bitcoinValueInDate);
}

/* getTotalValue
*
*   Multiplies howManyBitcoins * bitcoinValue_in_date = resultToPrint
*
*   Returns:
*       resultToPrint => Total value of bitcoins for that date
*/
float getTotalValue (std::string line)
{
    // std::cout << CYAN "--------------------------getTotalValue ------------------------ " RESET_COLOUR << std::endl;
    
    /* How many bitcoins did we have that day? */
    float howManyBitcoins = atoi(line.substr(12).c_str()); /* Gets line from input.txt */
    // std::cout << "> ✅ howManyBitcoins = " << howManyBitcoins << std::endl;
    
    /* Which was bitcoin's value that day? */
    float bitcoinValue_in_date = getValueInDate(line);
    // std::cout << ">🔜 Bitcoin's value we'll use: " << CYAN << bitcoinValue_in_date << RESET_COLOUR << std::endl;
    
    float resultToPrint = howManyBitcoins * bitcoinValue_in_date;
    // std::cout << CYAN "-----------------------------------------------------------------------" RESET_COLOUR<< std::endl;
    return (resultToPrint);
}