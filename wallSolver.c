//
// Created by Rob Schlom 11/3/17.
//
#include <stdio.h>
#include <stdbool.h>

void solveWall(int values[], int length);
bool isValid (int values[], int thisRun[], int length);
void printQuestion (int values[], int length);
void solveDangerWall(int values[], int length);
void printValues (int values[], int length);

int main(){
	int numBlocks = 0;
	printf("[ ][ ][ ][ ][ ][ ]\n");
	printf(" X  a  b  c  d  X\n");
	printf("You should have y blocks and y-2 values between 1-2 inclusive\n");
	printf("Not ment for edges, but may give accurate info about them if you\n");
	printf("treat edges like they have a unknown square hanging off the edge.\n");
	printf("How many blocks?: ");
	scanf("%d", &numBlocks);
	int values[numBlocks];
	values[0] = 0;
	values[numBlocks-1] = 0;
	printf("First Value: ");
	scanf("%d", &values[1]);
	while (values[1] > 2 || values[1] < 1){
		printf ("Try again: ");
		scanf("%d", &values[1]);
	}
	for (int i = 2; i<numBlocks-1; i++){
		printf("Next Value: ");
		scanf("%d", &values[i]);
		if (values[i] > 2 || values[i] < 1){
			printf("Try again\n");
			i--;
		}
	}
	solveWall(values, numBlocks);
}

void solveWall(int values[], int length){
	bool impossible = false;
	int knownSquares[length];
	int hadBomb[length];
	int hadNoBomb[length];
	//Set all three to 0
	for (int i = 0; i<length; i++){
		hadNoBomb[i] = 0;
		hadBomb[i] = 0;
		knownSquares[i] = -1;
	}
	bool allHadBoth = false;
	while(!allHadBoth){
		int index = 0;
		int thisRun[length];
		int thisRunD[length];
		//All of this run is -1
		for (int l = 0; l<length; l++){
			thisRun[l] = -1;
			thisRunD[l] = -1;
		}
		//Look for the first index that hasn't been both
		for (int i = 0; i < length; i++){
			if (hadBomb[i] == 0 || hadNoBomb[i] == 0){
				if (hadBomb[i] == 0){
					thisRun[i] = 1;
					thisRunD[i] = 1;
					index = i;
					//hadBomb[i] = 1;
					i = length;
				}
				else{
					thisRun[i] = 0;
					thisRunD[i] = 0;
					index = i;
					//hadNoBomb[i] = 1;
					i = length;
				}
			}
		}
		//printf("%d\n", index);
		//Filling in the right of the found index
		for (int j = index; j < length-1; j++){
			//bomb at j
			if (thisRun[j] == 1){
				//first or last element
				if (values[j] == 0){
					if (values[j+1] == 1){
						thisRun[j+1] = 0;
						//thisRunD[j+1] = 0;
						//hadNoBomb[j+1] = 1;
					}
					//Danger case, bomb could be at j+1 or j+2
					else{
						//printf("Danger\n");
						thisRun[j+1] = 1;
						//thisRunD[j+1] = 0;
						//hadBomb[j+1] = 1;
					}
				}
				else if (values[j] == 1){
					thisRun[j+1] = 0;
					//thisRunD[j+1] = 0;
					//hadNoBomb[j+1] = 1;
				}
				//value = 2
				else{
					//first value so left and right are unknown
					if (j == index && index != length-1){
						if (values[j+1] == 1){
							thisRun[j+1] = 0;
							//thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j+1 or j-1
						else{
							//printf("Danger\n");
							thisRun[j+1] = 1;
							//thisRunD[j+1] = 0;
							//hadBomb[j+1] = 1;
						}
					}
					else if (j != index){
						if (thisRun[j-1] == 1){
							thisRun[j+1] = 0;
							//thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						else{
							thisRun[j+1] = 1;
							//thisRunD[j+1] = 1;
							//hadBomb[j+1] = 1;
						}
					}
				}
			}
			//no bomb at j
			else{
				if (values[j] == 0){
					if (values[j+1] == 2){
						thisRun[j+1] = 1;
						//thisRunD[j+1] = 1;
					}
					//Danger case: bomb could be at j+1 or j+2
					else{
						//printf("Danger\n");
						thisRun[j+1] = 1;
						//thisRunD[j+1] = 0;
					}
				}
				else if (values[j] == 2){
					thisRun[j+1] = 1;
					//thisRunD[j+1] = 1;
					//hadBomb[j+1] = 1; 
				}
				//values[j] == 1
				else{
					if (j == index){
						if (j == 0){
							thisRun[j+1] = 1;
							//thisRunD[j+1] = 1;

							//hadBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j-1 or j+1
						else{
							//printf("Danger\n");
							thisRun[j+1] = 1;
							//thisRunD[j+1] = 0;
							//hadBomb[j+1] = 1;
						}
					}
					else{
						if (thisRun[j-1] == 1){
							thisRun[j+1] = 0;
							//thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j-1 or j+1: that might be a lie
						else{
							//printf("Danger\n");
							thisRun[j+1] = 1;
							//thisRunD[j+1] = 1;
							//hadBomb[j+1] = 1;
						}
					}
				}
			}
			if (thisRunD[j] == 1){
				//first or last element
				if (values[j] == 0){
					if (values[j+1] == 1){
						//thisRun[j+1] = 0;
						thisRunD[j+1] = 0;
						//hadNoBomb[j+1] = 1;
					}
					//Danger case, bomb could be at j+1 or j+2
					else{
						//printf("Danger\n");
						//thisRun[j+1] = 1;
						thisRunD[j+1] = 0;
						//hadBomb[j+1] = 1;
					}
				}
				else if (values[j] == 1){
					//thisRun[j+1] = 0;
					thisRunD[j+1] = 0;
					//hadNoBomb[j+1] = 1;
				}
				//value = 2
				else{
					//first value so left and right are unknown
					if (j == index && index != length-1){
						if (values[j+1] == 1){
							//thisRun[j+1] = 0;
							thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j+1 or j-1
						else{
							//printf("Danger\n");
							//thisRun[j+1] = 1;
							thisRunD[j+1] = 0;
							//hadBomb[j+1] = 1;
						}
					}
					else if (j != index){
						if (thisRunD[j-1] == 1){
							//thisRun[j+1] = 0;
							thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						else{
							//thisRun[j+1] = 1;
							thisRunD[j+1] = 1;
							//hadBomb[j+1] = 1;
						}
					}
				}
			}
			//no bomb at j
			else{
				if (values[j] == 0){
					if (values[j+1] == 2){
						//thisRun[j+1] = 1;
						thisRunD[j+1] = 1;
					}
					//Danger case: bomb could be at j+1 or j+2
					else{
						//printf("Danger\n");
						//thisRun[j+1] = 1;
						thisRunD[j+1] = 0;
					}
				}
				else if (values[j] == 2){
					//thisRun[j+1] = 1;
					thisRunD[j+1] = 1;
					//hadBomb[j+1] = 1; 
				}
				//values[j] == 1
				else{
					if (j == index){
						if (j == 0){
							//thisRun[j+1] = 1;
							thisRunD[j+1] = 1;

							//hadBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j-1 or j+1
						else{
							//printf("Danger\n");
							//thisRun[j+1] = 1;
							thisRunD[j+1] = 0;
							//hadBomb[j+1] = 1;
						}
					}
					else{
						if (thisRunD[j-1] == 1){
							//thisRun[j+1] = 0;
							thisRunD[j+1] = 0;
							//hadNoBomb[j+1] = 1;
						}
						//Danger case: bomb could be at j-1 or j+1: that might be a lie
						else{
							//printf("Danger\n");
							//thisRun[j+1] = 1;
							thisRunD[j+1] = 1;
							//hadBomb[j+1] = 1;
						}
					}
				}
			}
		}
		//printf("Right Side\n");
		//printQuestion(thisRun, length);
		//printf("Right Side D\n");
		//printQuestion(thisRunD, length);
		//create solutions from left of index
		for (int l = index; l>=1; l--){
			//bomb at l
			if (thisRun[l] == 1){
				if (values[l] == 1){
					thisRun[l-1] = 0;
					//thisRunD[l-1] = 0;
					//hadNoBomb[l-1] = 1;
				}
				//index is last spot
				else if (values[l] == 0){
					if (values[l-1] == 1){
						thisRun[l-1] = 0;
						//thisRunD[l-1] = 0;
					}
					//Danger case: bomb couls be at j-1 or j-2
					else{
						//printf("Danger\n");
						thisRun[l-1] = 1;
						//thisRunD[l-1] = 0;
					}
				}
				else{
					if (thisRun[l+1] == 1){
						thisRun[l-1] = 0;
						//thisRunD[l-1] = 0;
						//hadNoBomb[l-1] = 1;
					}
					else{
						thisRun[l-1] = 1;
						//thisRunD[l-1] = 1;
						//hadBomb[l-1] = 1;
					}
				}
			}
			//no bomb at l
			else{
				if (values[l] == 2){
					thisRun[l-1] = 1;
					//thisRunD[l-1] = 1;
					//hadBomb[l-1] = 1;
				}
				else if (values[l] == 0){
					if (values[l-1] == 2){
						thisRun[l-1] = 1;
						//thisRunD[l-1] = 1;
					}
					//Danger case: bomb could be at j-1 or j-2
					else{
						//printf("Danger\n");
						thisRun[l-1] = 1;
						//thisRunD[l-1] = 0;
					}
				}
				//values[l] == 1	
				else{
					if (thisRun[l+1] == 1){
						thisRun[l-1] = 0;
						//thisRunD[l-1] = 0;
						//hadNoBomb[l-1] = 1;
					}
					else{
						thisRun[l-1] = 1;
						//thisRunD[l-1] = 1;
						//hadBomb[l-1] = 1;
					}
				}
			}
			if (thisRunD[l] == 1){
				if (values[l] == 1){
					//thisRun[l-1] = 0;
					thisRunD[l-1] = 0;
					//hadNoBomb[l-1] = 1;
				}
				//index is last spot
				else if (values[l] == 0){
					if (values[l-1] == 1){
						//thisRun[l-1] = 0;
						thisRunD[l-1] = 0;
					}
					//Danger case: bomb couls be at j-1 or j-2
					else{
						//printf("Danger\n");
						//thisRun[l-1] = 1;
						thisRunD[l-1] = 0;
					}
				}
				else{
					if (thisRunD[l+1] == 1){
						//thisRun[l-1] = 0;
						thisRunD[l-1] = 0;
						//hadNoBomb[l-1] = 1;
					}
					else{
						//thisRun[l-1] = 1;
						thisRunD[l-1] = 1;
						//hadBomb[l-1] = 1;
					}
				}
			}
			//no bomb at l
			else{
				if (values[l] == 2){
					//thisRun[l-1] = 1;
					thisRunD[l-1] = 1;
					//hadBomb[l-1] = 1;
				}
				else if (values[l] == 0){
					if (values[l-1] == 2){
						//thisRun[l-1] = 1;
						thisRunD[l-1] = 1;
					}
					//Danger case: bomb could be at j-1 or j-2
					else{
						//printf("Danger\n");
						//thisRun[l-1] = 1;
						thisRunD[l-1] = 0;
					}
				}
				//values[l] == 1	
				else{
					if (thisRunD[l+1] == 1){
						//thisRun[l-1] = 0;
						thisRunD[l-1] = 0;
						//hadNoBomb[l-1] = 1;
					}
					else{
						//thisRun[l-1] = 1;
						thisRunD[l-1] = 1;
						//hadBomb[l-1] = 1;
					}
				}
			}
		}
		//see if thisRun is a valid solution, if not, then we know index must be the opposite of what it was set to
		//printf("Final thisRun\n");
		//printQuestion(thisRun, length);
		//printf("Final thisRunD\n");
		//printQuestion(thisRunD, length);
		bool valid = isValid(values, thisRun,length);
		bool validD = isValid(values, thisRunD, length);
		if (!valid && !validD){
			if (knownSquares[index] != -1){
				impossible = true;
			}
			if (thisRun[index] == 1){
				hadBomb[index] = 1;
				knownSquares[index] = 0;
			}
			else{
				hadNoBomb[index] = 1;
				knownSquares[index] = 1;
			}
		}
		else{
			if (valid){
				for (int m = 0; m<length; m++){
					if (thisRun[m] ==0){
						hadNoBomb[m] = 1;
					}
					else{
						hadBomb[m] = 1;
					}
				}
			}
			else{
				for (int n = 0; n<length; n++){
					if (thisRunD[n] == 0){
						hadNoBomb[n] = 1;
					}
					else{
						hadBomb[n] = 1;
					}
				}
			}
		}
		//Checks if we've tried all the solutions	
		for (int k = 0; k<length; k++){
			if (hadBomb[k] == 1 && hadNoBomb[k] == 1){
				allHadBoth = true;
				continue;
			}
			else{
				allHadBoth = false;
				k = length;
			}
		}
	}
	printf("\n");
	if (impossible){
		printf("Too hard for me\nHere's my guess\n");
	}
	printQuestion (knownSquares, length);
	printValues (values, length);
}

bool isValid (int values[], int thisRun[], int length){
	for (int i = 1; i<length-1; i++){
		if (values[i] == 1){
			if (thisRun[i-1] + thisRun[i] + thisRun[i+1] != 1){
				return false;
			}
		}
		else{
			if (thisRun[i-1] + thisRun[i] + thisRun[i+1] != 2){
				return false;
			}
		}
	}
	return true;
}

void printQuestion (int values[], int length){
	for (int i = 0; i < length; i++){
		if (values[i] == -1){
			printf ("[?]");
		}
		else if (values[i] == 0){
			printf("[ ]");
		}
		else{
			printf("[B]");
		}
	}
	printf("\n");
}
void printValues (int values[], int length){
	printf("   ");
	for (int i = 1; i<length-1; i++){
		printf("|%d|", values[i]);
	}
	printf("\n");
}