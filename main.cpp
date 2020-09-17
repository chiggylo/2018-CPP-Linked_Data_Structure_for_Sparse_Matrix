
#include <iostream>
#include <vector>
#include <string>


using namespace std;

// structure of the node for storing the next row and the next column
struct nodeCol {
	int index; 
	struct nodeCol *nextCN;
	struct nodeRow *nextRN;
};

// structure of the node for storing the data and the next column
struct nodeRow {
	int index;
	int data;
	struct nodeRow *nextRN;
};

class UTM {
public:
	int index;
	int size; // size of the matrix
	struct nodeCol *head;
	UTM(int dimension, int indexing) {
		index = indexing; 
		head = NULL;
		size = dimension;
		cout << "Initialising Matrix..." << endl;
		for (int i = 0; i < size; i++) { // loop for rows
			struct nodeCol *startCol = new (struct nodeCol);

			// creating column node and initialise values
			struct nodeCol *newRow = new (struct nodeCol);
			newRow->index = i;
			newRow->nextCN = NULL;
			newRow->nextRN = NULL;

			if (head == NULL) {
				// inserting node in column
				head = newRow;
				startCol = head;
				for (int j = i; j < size; j++) { // loop for columns
					struct nodeRow *startRow = new (struct nodeRow);

					// creating row node
					struct nodeRow *newCol = new (struct nodeRow);
					newCol->index = j;
					newCol->nextRN = NULL;
					newCol->data = 0;

					// inserting node in row
					if (startCol->nextRN == NULL) {
						startCol->nextRN = newCol;
					}
					else {
						startRow = startCol->nextRN;
						while (startRow->nextRN != NULL) {
							startRow = startRow->nextRN;
						}
						startRow->nextRN = newCol;
					}

				}
			}
			else { // if list isn't empty
				startCol = head;
				while (startCol->nextCN != NULL) { // scrolling to the last slot
					startCol = startCol->nextCN;
				}
				startCol->nextCN = newRow;
				startCol = startCol->nextCN;
				for (int j = i; j < size; j++) { // loop for columns
					struct nodeRow *startRow = new (struct nodeRow);

					// creating row node
					struct nodeRow *newCol = new (struct nodeRow);
					newCol->index = j;
					newCol->nextRN = NULL;
					newCol->data = 0;

					// inserting node in row
					if (startCol->nextRN == NULL) {
						startCol->nextRN = newCol;
					}
					else {
						startRow = startCol->nextRN;
						while (startRow->nextRN != NULL) {
							startRow = startRow->nextRN;
						}
						startRow->nextRN = newCol;
					}

				}
			}
		}
	}
	bool inputElements(int row, int col, int value);
	void displayMatrix();
	void sumUTM(vector<UTM> &matrix, UTM u1, UTM u2);
	void displayMatrixWithout();
};

void UTM::displayMatrixWithout() {
	struct nodeCol *currentCol = new (struct nodeCol);
	struct nodeRow *currentRow = new (struct nodeRow);

	if (head == NULL) { // if empty stop processing
		cout << "Empty" << endl;
		return;
	}
	else {
		int r = 2;
		currentCol = head;
		cout << "Displaying Matrix..." << endl;
		while (currentCol->nextCN != NULL) { // scrolling through row
			currentRow = currentCol->nextRN;

			while (currentRow->nextRN != NULL) { // scrolling through column
				cout << currentRow->data << "\t";
				currentRow = currentRow->nextRN;
			}
			cout << currentRow->data << "\n";
			for (int i = 1; i < r; i++) {
				cout << "0\t";
			}
			r++;
			currentCol = currentCol->nextCN;
		}
		currentRow = currentCol->nextRN;
		while (currentRow->nextRN != NULL) {
			cout << currentRow->data << "\t";
			currentRow = currentRow->nextRN;
		}
		cout << currentRow->data << "\n";
		return;
	}
}


void UTM::sumUTM(vector<UTM> &matrix, UTM u1, UTM u2) {
	if (u1.size != u2.size) { // additional error checking
		cout << "Not matching dimension\n";
		return;
	}
	matrix.push_back(UTM(u1.size, matrix.size())); // creating new matrix for the sum of 2 matrices

	struct nodeCol *currentCol1 = new (struct nodeCol);
	struct nodeRow *currentRow1 = new (struct nodeRow);
	struct nodeCol *currentCol2 = new (struct nodeCol);
	struct nodeRow *currentRow2 = new (struct nodeRow);
	struct nodeCol *currentCol3 = new (struct nodeCol);
	struct nodeRow *currentRow3 = new (struct nodeRow);

	currentCol1 = u1.head;
	currentCol2 = u2.head;
	currentCol3 = matrix.back().head;
	while (currentCol1->nextCN != NULL) { // scroll through the rows
		currentRow1 = currentCol1->nextRN;
		currentRow2 = currentCol2->nextRN;
		currentRow3 = currentCol3->nextRN;

		while (currentRow1->nextRN != NULL) { // scroll through the columns
			currentRow3->data = currentRow1->data + currentRow2->data;

			currentRow1 = currentRow1->nextRN;
			currentRow2 = currentRow2->nextRN;
			currentRow3 = currentRow3->nextRN;
		}
		currentRow3->data = currentRow1->data + currentRow2->data;
		currentCol1 = currentCol1->nextCN;
		currentCol2 = currentCol2->nextCN;
		currentCol3 = currentCol3->nextCN;

	}

	currentRow1 = currentCol1->nextRN;
	currentRow2 = currentCol2->nextRN;
	currentRow3 = currentCol3->nextRN;
	while (currentRow1->nextRN != NULL) {
		currentRow3->data = currentRow1->data + currentRow2->data;
		currentRow1 = currentRow1->nextRN;
		currentRow2 = currentRow2->nextRN;
		currentRow3 = currentRow3->nextRN;
	}
	currentRow3->data = currentRow1->data + currentRow2->data;
	matrix.back().displayMatrix();
}


bool UTM::inputElements(int row, int col, int value) {
	if (col > size || row > size) { // error checking
		return false;
	}
	if (col < row) { // error checking
		cout << "Invalid: not a non-zero element" << endl;
		return false;
	}
	struct nodeCol *currentCol = new (struct nodeCol);
	struct nodeRow *currentRow = new (struct nodeRow);

	currentCol = head;
	while (currentCol->index != row) { // scroll to the specific row
		currentCol = currentCol->nextCN;
	}
	currentRow = currentCol->nextRN;
	while (currentRow->index != col) { // scroll to the specific column
		currentRow = currentRow->nextRN;
	}
	currentRow->data = value; // insert value
	return true;
}

void UTM::displayMatrix() {
	struct nodeCol *currentCol = new (struct nodeCol);
	struct nodeRow *currentRow = new (struct nodeRow);

	if (head == NULL) { // if empty stop processing
		cout << "Empty" << endl;
		return;
	}
	else {
		int r = 2;
		currentCol = head;
		cout << "Displaying Matrix..." << endl;
		while (currentCol->nextCN != NULL) { // scrolling through row
			currentRow = currentCol->nextRN;

			while (currentRow->nextRN != NULL) { // scrolling through column
				cout << "[(" << currentCol->index + 1 << " ," << currentRow->index + 1 << "): " << currentRow->data << "]" << "\t";
				currentRow = currentRow->nextRN;
			}
			cout << "[(" << currentCol->index + 1 << " ," << currentRow->index + 1 << "): " << currentRow->data << "]\n";
			for (int i = 1; i < r; i++) {
				cout << "[(" << r << ", " << i << "): 0]\t";
			}
			r++;
			currentCol = currentCol->nextCN;
		}
		currentRow = currentCol->nextRN;
		while (currentRow->nextRN != NULL) {
			cout << "[(" << currentCol->index + 1 << " ," << currentRow->index + 1 << "): " << currentRow->data << "]" << "\t";
			currentRow = currentRow->nextRN;
		}
		cout << "[(" << currentCol->index + 1 << " ," << currentRow->index + 1 << "): " << currentRow->data << "]" << "\n";
		return;
	}
}

int main()
{

	vector<UTM> matrix;
	cout << "----------------------------------------------------------\n";
	cout << "   LINKED DATA STRUCTURE for UPPER TRIANGULAR MATRICES\n";
	cout << "----------------------------------------------------------\n";


	while (true) {
		int choice, dimension, row, col, value, m1, m2;
		string check;
		cout << "1: Create new matrix\n2: Input value\n3: Display Matrix\n4: Display Matrix without Coordinate\n5: Sum of 2 Matrix\n6: Delete Matrix\n7: Exit" << endl;
		cin >> choice; // select choice
		while (cin.fail()) // error checking choice
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> choice;
		}
		cout << "----------------------------------------------------------\n";
		switch (choice) {
		case 1:
			cout << "Size of new matrix: ";
			cin >> dimension;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> dimension;
			}
			cout << "----------------------------------------------------------\n";
			if (dimension <= 0) {
				cout << "Invalid dimension" << endl;
				break;
			}
			matrix.push_back(UTM(dimension, matrix.size()));
			matrix.back().displayMatrix();
			break;
		case 2:
			if (matrix.size() == 0) {
				cout << "No matrix available" << endl;
				break;
			}
			if (matrix.size() < 4) {
				for (int i = 0; i < matrix.size(); i++) {
					cout << "Matrix " << i << "\n";
					matrix.at(i).displayMatrix();
					cout << "\n";
				}
			}
			cout << "Which matrix?" << endl;
			cin >> choice;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> choice;
			}
			cout << "----------------------------------------------------------\n";
			if (choice < 0 || choice > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			matrix.at(choice).displayMatrix();
			cout << "(X,Y) input index for X: ";
			cin >> row;
			while (cin.fail())
			{
				cout << "Invalid Entry\n" << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> row;
			}
			cout << "----------------------------------------------------------\n";
			cout << "(X,Y) input index for Y: ";
			cin >> col;
			while (cin.fail())
			{
				cout << "Invalid Entry\n" << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> col;
			}
			cout << "----------------------------------------------------------\n";
			cout << "Enter value: ";
			cin >> value;
			while (cin.fail())
			{
				cout << "Invalid Entry\n" << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> value;
			}
			cout << "----------------------------------------------------------\n";
			if (row < 1 || col < 1 || col > matrix.at(choice).size || row >> matrix.at(choice).size) {
				cout << "Invalid Entry of Coordinate\n";
				break;

			}
			else {
				if (matrix.at(choice).inputElements(row - 1, col - 1, value)) {
					cout << "Updating matrix...\n";

				};
				matrix.at(choice).displayMatrix();
			}
			break;
		case 3:
			if (matrix.size() == 0) {
				cout << "No matrix available" << endl;
				break;
			}
			cout << "Which matrix? 0 - " << matrix.size() - 1 << endl;
			cin >> choice;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> choice;
			}
			if (choice < 0 || choice > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			cout << "----------------------------------------------------------\n";
			matrix.at(choice).displayMatrix();
			break;
		case 4:
			if (matrix.size() == 0) {
				cout << "No matrix available" << endl;
				break;
			}
			cout << "Which matrix? 0 - " << matrix.size() - 1 << endl;
			cin >> choice;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> choice;
			}
			if (choice < 0 || choice > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			cout << "----------------------------------------------------------\n";
			matrix.at(choice).displayMatrixWithout();
			break;
		case 5:
			if (matrix.size() == 0) {
				cout << "No matrix available" << endl;
				break;
			}
			cout << "First Matrix (0 - " << matrix.size() - 1 << "): " << endl;
			cin >> m1;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> m1;
			}
			if (m1 < 0 || m1 > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			cout << "----------------------------------------------------------\n";

			cout << "Second Matrix (0 - " << matrix.size() - 1 << "): " << endl;
			cin >> m2;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> m2;
			}
			if (m2 < 0 || m2 > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			cout << "----------------------------------------------------------\n";
			matrix.at(m1).sumUTM(matrix, matrix.at(m1), matrix.at(m2));
			break;
		case 6:
			if (matrix.size() == 0) {
				cout << "No matrix available" << endl;
				break;
			}
			cout << "Which matrix? 0 - " << matrix.size() - 1 << endl;
			cin >> choice;
			while (cin.fail())
			{
				cout << "Invalid Entry\nEnter 0-" << matrix.size() - 1 << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> choice;
			}
			cout << "----------------------------------------------------------\n";
			if (choice < 0 || choice > matrix.size() - 1) {
				cout << "Invalid choice" << endl;
				break;
			}
			cout << "Deleting matrix...\n";
			matrix.erase(matrix.begin() + matrix.at(choice).index);
			break;
		case 7:
			cout << "Exiting..." << endl;
			return 0;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		cout << "----------------------------------------------------------\n";
	}
	return 0;
}