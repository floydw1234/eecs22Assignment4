/* Author: William Floyd */
/* Josephus.c Exersize 1 */

#include <stdio.h>

int findMaxKills(int array[], int length){
    int max = array[0];
    for(int i = 1; i < length; i++){
        if( array[i] > max)
            max = array[i];
    }
    return max;
}

void printArray(int array[], int length){
    for(int i = 0; i < length ; i++){
        printf("%d\n",array[i]);

    }
    printf("--------\n");
}

int checkIfThereIsOnePerson(int array[], int count){
    //printArray(array, count);
    int counter = 0;
    int index = 0;
    for(int i = 0; i < count ; i++){
        if(array[i] == 1){
            counter += 1;
            index = i;
        }
    }
    if(counter == 1){
        return index;
    }else{
        return -1;
    }
}



int moveAndExcecute(int array[],int length, int start, int killCount[]){
        int position = start;
        if(start == length - 1)
            position = 0;
        else
            position ++;
        /*printf("length: %d\n", length);
        printf("initial Position: %d\n", position); */
        while( array[position] == 0){
            if(position == length - 1){
                position = 0;
            }else{
                position ++;
            }
        }

        int victim = position + 1; //starting to find the victim of the killer
        if(victim == length)
            victim = 0;



        while(array[victim] == 0){
            if(victim == length-1)
                victim = 0;
            else
                victim ++;
        }
        killCount[position] = killCount[position] + 1;
        /*printf("victim: %d\n", victim);
        printf("killer: %d\n",position);
        printf("---------\n");*/
        array[victim] = 0; // the excectution
        return position;
}


int josephus(int peopleCount, int startingPoint, int people[], int killCount[]){

    //memset(people, 0, peopleCount*sizeof(int));
    for(int i = 0; i < peopleCount; i++){
        people[i] = 1;
    }
    int currentPosition = startingPoint -1;
    people[currentPosition + 1] = 0; // first Excecution
   


    while( checkIfThereIsOnePerson(people, peopleCount) == -1){
        currentPosition = moveAndExcecute(people,peopleCount, currentPosition, killCount);
     

    }
    return checkIfThereIsOnePerson(people, peopleCount);
}

int main(){
    int people[1000] = {};
    int killCount[1000] = {};
    int numberOfPeople;
    int startingPoint;
    printf("Enter the Amount of people in the josephus circle: ");
    scanf("%d",&numberOfPeople);
    printf("Enter the starting Position of the first executionor: ");
    scanf("%d",&startingPoint);

    int answer = josephus(numberOfPeople,startingPoint, people, killCount);
    printf("Spot %d is safe.\n",answer + 1);
    printf("Most kills by an individual is: %d\n",findMaxKills(killCount, numberOfPeople));
    return 0;
}
