#include "order_of_operations.h"

OrderOfOperations::OrderOfOperations(QWidget* parent) : ConfigWindowBase(parent)
{
}

void OrderOfOperations::ReadXmlFileImp(QString) {

}

void OrderOfOperations::WriteXmlFileImp(QString) {

}

bool OrderOfOperations::CheckEmpty() {

}

QString OrderOfOperations::HelpImp() {
    QString str = "Stage 1\n"
                  "Set the number of operators and difficulty level for stage 1.\n"
                  "Difficulty level must be a number between 1 - 3.\n"
                  "Difficulty level 1 --- Equations generated only has + and * operators\n"
                  "Difficulty level 2 --- Equations generated has +, -, * and / operators\n"
                  "Difficulty level 3 --- Equations generated has +, -, *"
                  "and / operators as well as parentheses (2 parentheses at most)\n\n"
                  "Stage 2\n"
                  "Input equations that you would like to appear in stage 2.\n"
                  "Add a space between each number and operator, as shown in the sample equation.\n"
                  "All operators will be substituted with blanks when they appear in stage 2.\n"
                  "Equations are randomly chosen for each team from the pool of equations given.\n"
                  "Equations that are too long may appear cramped.No negative numbers.";

    return str;
}
