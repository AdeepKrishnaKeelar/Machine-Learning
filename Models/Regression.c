/* 
    Covariation of two independent magnitudes is known as correlation. If two variables x and y
    are related in such a way increase or decrease in any of them corresponds to the increase or
    decrease in the other, then they are positively correlated. Else, the opposite leads to 
    negatively correlated. 

    Numerical measure of correlation between two values is Karl Pearsons Coefficient of Correlation.

            r = ∑(x-x')(y-y')/n σx σy
            σx = (x-x')/n

    Regression is the estimation of one independent variable in terms of other. 


    Simple Problem -- 
    Data entered Age of Wife (Y) and Age of Husband (X) in years. Form Regression Lines and calculate 
    the age of husband for entered age of wife. 
*/

/* 
    Step 1 - Take input. 
    Step 2 - Set up table with X,Y columns having their summation values and squared summation values.
    Step 3 - Calculate XBar, YBar, ZBar and SigmaX, SigmaY and SigmaZ values.
    Step 4 - Calculate the Karl Pearson's coefficient. 
    Step 5 - Set up the regression lines. Entered to be checked is wife's age. Result Husband's Age.
*/

    #include<stdio.h>
    #include<math.h> //use -lm
    #include<stdbool.h>
    #include<stdlib.h>


    //Global variables that are key for the equations.
    int XSummation=0, YSummation=0, ZSummation=0;
    int XSqSummation=0, YSqSummation=0, ZSqSummation=0;
    int XBar=0,YBar=0,ZBar=0;
    float sigmaX=0.0,sigmaY=0.0;
    float sigmaSqX=0.0,sigmaSqY=0.0,sigmaSqZ=0.0;
    float KPCoefficient=0.0;

    //Linked list to house the data for "learning"?
    struct Data {
        int XValue,YValue;
        int XValueSq,YValueSq;
        int ZValue,ZValueSq;
        struct Data *NextPointer;
    };

    //Simple insertion to the front of the linked list.
    void InsertIntoLinkedList(struct Data **head_pointer, int x_val,int y_val) {
        struct Data* newData = (struct Data*)malloc(sizeof(struct Data));
        newData->XValue=x_val;
        XSummation+=newData->XValue;
        newData->YValue=y_val;
        YSummation+=newData->YValue;
        newData->NextPointer=(*head_pointer);
        *head_pointer=newData;
    }

    //Function to set up simple table with manipulated input values. Some of the global variables
    //get their values from here.
    void setUpCalculationTable(struct Data* head) {
        int temp_sum_x=0,temp_sum_y=0;
        if(head==NULL) {
            printf("No elements accessed!");
        } else {
            while(head!=NULL) {
                head->XValueSq=pow(head->XValue,2);
                XSqSummation+=head->XValueSq;
                head->YValueSq=pow(head->YValue,2);
                YSqSummation+=head->YValueSq;
                head->ZValue=head->XValue-head->YValue;
                ZSummation+=head->ZValue;
                head->ZValueSq=pow(head->ZValue,2);
                ZSqSummation+=head->ZValueSq;
                head=head->NextPointer;
            }
        }
    }

    //SigmaX,SigmaY and SigmaZ and X',Y',Z' get their values here.
    void setUpBarandSigmaValues(int SizeOfData) {
        XBar=XSummation/SizeOfData;
        YBar=YSummation/SizeOfData;
        ZBar=ZSummation/SizeOfData;

        sigmaSqX= (XSqSummation/SizeOfData)-pow(XBar,2);
        sigmaX=sqrt(sigmaSqX);
        sigmaSqY= (YSqSummation/SizeOfData)-pow(YBar,2);
        sigmaY=sqrt(sigmaSqY);
        sigmaSqZ= (ZSqSummation/SizeOfData)-pow(ZBar,2);
    }

    //The important Pearsons coefficient value gets its value here.
    void calculateKarlPearsonsCoefficient() {
        KPCoefficient=(sigmaSqX+sigmaSqY-sigmaSqZ)/(2*sigmaX*sigmaY);
    }

    //The Regression prediction is made here. 
    //Note - Only one equation to find husband's age is found here.
    //Wife's age regression line to be inserted shortly. 
    void makeRegressionPrediction(int numberToBeChecked) {
        float temp_x=0.0;
        temp_x=((KPCoefficient*sigmaX)/sigmaY)*(numberToBeChecked-YBar)+XBar;
        printf("The prediction value is --- %.2f\n",temp_x);
        printf("The approximate whole value is --- %.0f\n",roundf(temp_x));
    }

    //Display the linked list.
    void DisplayData(struct Data* head) {
        if(head==NULL) {
            printf("No elements present!");
        } else {
            while(head!=NULL) {
                printf("%d %d %d %d %d %d\n",head->XValue,head->YValue,head->ZValue,head->XValueSq,head->YValueSq,head->ZValueSq);
                head=head->NextPointer;
            }
        }
    }

    //Display all the global values.
    void DisplayRealInfo() {
        printf("X Summation -- %d\n",XSummation);
        printf("Y Summation -- %d\n",YSummation);
        printf("Z Summation -- %d\n",ZSummation);
        printf("X Square Summation -- %d\n",XSqSummation);
        printf("Y Square Summation -- %d\n",YSqSummation);
        printf("Z Square Summation -- %d\n",ZSqSummation);
        printf("X Bar -- %d\n",XBar);
        printf("Y Bar -- %d\n",YBar);
        printf("Z Bar -- %d\n",ZBar);
        printf("Sigma X and Sigma X square -- %.2f, %.2f\n",sigmaX,sigmaSqX);
        printf("Sigma Y and Sigma Y square -- %.2f, %.2f\n",sigmaY,sigmaSqY);
        printf("Sigma Z -- %.2f\n",sigmaSqZ);
        printf("Karl Pearsons Coefficient value -- %.2f\n",KPCoefficient);  
    }

    int main(int argc, char* args[]) {
        int SizeOfData=0;
        int temp_x,temp_y;
        int numberToBeChecked;
        printf("Enter the wife's age to predict husband's age -- ");
        scanf("%d",&numberToBeChecked);
        struct Data *headPtr=NULL;
        FILE* DataFile = fopen("Training Data.txt","r");
        if(DataFile==NULL) {
            printf("Error in opening the file!");
            return EXIT_FAILURE;
        } else {
            while(fscanf(DataFile,"%d %d",&temp_x,&temp_y)!=EOF) {
                InsertIntoLinkedList(&headPtr,temp_x,temp_y);
                SizeOfData+=1;
            }
        }

        fclose(DataFile); //close files, save memory.

        setUpCalculationTable(headPtr);
        setUpBarandSigmaValues(SizeOfData);
        calculateKarlPearsonsCoefficient();
        DisplayData(headPtr);
        free(headPtr); //free memory, save computers.
        DisplayRealInfo();
        makeRegressionPrediction(numberToBeChecked);

        return EXIT_SUCCESS;
    }