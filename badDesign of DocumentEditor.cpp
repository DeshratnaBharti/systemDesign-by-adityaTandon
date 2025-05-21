#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DocumentEditor {
private:
    vector<string> documentElements;
    string renderedDocument;

public:
    // Adds text as a plain string
    void addText(string text) {
        documentElements.push_back(text);
    }

    // Adds an image represented by its file path
    void addImage(string imagePath) {
        documentElements.push_back(imagePath);
    }

    // Renders the document by checking the type of each element at runtime
    string renderDocument() {
        if(renderedDocument.empty()) {
            string result;
            for (auto element : documentElements) {
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" ||
                 element.substr(element.size() - 4) == ".png")) {
                    result += "[Image: " + element + "]" + "\n";
                } else {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile() {
        ofstream file("document.txt");
        if (file.is_open()) {
            file << renderDocument();
            file.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

int main() {
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument() << endl;

    editor.saveToFile();
    
    return 0;
}


/***
🔧 How It Works (Step-by-Step)
1. Storing the Document
The document is built from multiple pieces, each of which is:

A plain string of text, or

An image filename (like "photo.jpg")

All these are stored in a vector called documentElements.

2. Adding Elements
addText("Hello, world!") → Adds a string to the document.

addImage("picture.jpg") → Adds an image path to the document.

These just append strings to the documentElements vector. The difference between text and image is not stored — instead, it's determined later when rendering, based on file extensions.

3. Rendering the Document (renderDocument)
This function combines all added elements into a final readable format. Here's how it decides how to format each element:

cpp
Copy
Edit
if (element ends with ".jpg" or ".png") {
    format as: [Image: filename]
} else {
    treat as plain text
}
Example:

cpp
Copy
Edit
addText("Hello")
addImage("image.jpg")
Results in:

arduino
Copy
Edit
Hello
[Image: image.jpg]
It also uses a cache (renderedDocument) so that rendering only happens once. If the user calls renderDocument() again, it returns the same result without recalculating it.

4. Saving to File (saveToFile)
The saveToFile() function:

Opens a file called "document.txt"

Writes the rendered document into that file

Closes the file

If it fails to open the file, it prints an error message.

✅ Summary of Functionality
Feature	How It Works
Add Text	Stored in a vector as a plain string
Add Image	Stored in the same vector; treated as an image if .jpg or .png
Render	Converts elements into a readable format (images shown as [Image: filename])
Save	Outputs the rendered document into document.txt

📌 Purpose
This is a basic simulation of a document editor. It’s not graphical—it simply builds a document as strings and writes to a file. It can be useful as a:

Practice example for object-oriented programming in C++

Simple template for future document processing features

Mini file generation utility
**/
