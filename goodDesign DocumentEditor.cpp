
#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;

// Abstraction for document elements
class DocumentElement {
public:
    virtual string render() = 0;
};

// Concrete implementation for text elements
class TextElement : public DocumentElement {
private:
    string text;

public:
    TextElement(string text) {
        this->text = text;
    }

    string render() override {
        return text;
    }
};

// Concrete implementation for image elements
class ImageElement : public DocumentElement {
private:
    string imagePath;

public:
    ImageElement(string imagePath) {
        this->imagePath = imagePath;
    }

    string render() override {
        return "[Image: " + imagePath + "]";
    }
};

// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabSpaceElement : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document {
private:
    vector<DocumentElement*> documentElements;

public:
    void addElement(DocumentElement* element) {
        documentElements.push_back(element);
    }

    // Renders the document by concatenating the render output of all elements.
    string render() {
        string result;
        for (auto element : documentElements) {
            result += element->render();
        }
        return result;
    }
};

// Persistence abstraction
class Persistence {
public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of Persistence
class FileStorage : public Persistence {
public:
    void save(string data) override {
        ofstream outFile("document.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistence {
public:
    void save(string data) override {
        // Save to DB
    }
};

// DocumentEditor class managing client interactions
class DocumentEditor {
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
    DocumentEditor(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    }

    void addText(string text) {
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath) {
        document->addElement(new ImageElement(imagePath));
    }

    // Adds a new line to the document.
    void addNewLine() {
        document->addElement(new NewLineElement());
    }

    // Adds a tab space to the document.
    void addTabSpace() {
        document->addElement(new TabSpaceElement());
    }

    string renderDocument() {
        if(renderedDocument.empty()) {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};

// Client usage example
int main() {
    Document* document = new Document();
    Persistence* persistence = new FileStorage();

    DocumentEditor* editor = new DocumentEditor(document, persistence);

    // Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and display the final document.
    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}
/*** It demonstrates several software engineering principles, including:

Abstraction

Inheritance

Polymorphism

Separation of Concerns (Single Responsibility Principle)

Extensibility

Let’s break it down clearly:

🧠 What This Code Does
This code creates a console-based document editor that allows users to:

Add text, images, new lines, and tab spaces

Render the document into a single formatted string

Save the document to a file (document.txt)

🧱 Main Components and Their Roles
1. Abstract Base Class: DocumentElement
This is a base interface for anything that can be part of a document.

It enforces that all elements must have a render() method.

cpp
Copy
Edit
class DocumentElement {
public:
    virtual string render() = 0;
};
2. Concrete Document Elements
These inherit from DocumentElement and implement the render() method:

Class	Purpose	render() Output
TextElement	Displays a text string	"Hello"
ImageElement	Displays an image (as text)	"[Image: picture.jpg]"
NewLineElement	Adds a new line	"\n"
TabSpaceElement	Adds a tab space	"\t"

3. Document Class
Manages a collection of DocumentElement*.

Combines all elements using their render() method to form the final document.

cpp
Copy
Edit
string render() {
    string result;
    for (auto element : documentElements) {
        result += element->render();
    }
    return result;
}
4. Persistence Abstraction
This uses another interface to separate storage logic:

cpp
Copy
Edit
class Persistence {
public:
    virtual void save(string data) = 0;
};
Concrete Implementation:
FileStorage: Saves to document.txt

DBStorage: Placeholder for future database saving

This separation allows you to swap storage methods easily without changing document or editor logic (open-closed principle).

5. DocumentEditor Class
The main interface for clients to interact with:

Receives a Document and a Persistence implementation

Offers methods like addText(), addImage(), addNewLine(), addTabSpace()

Renders the document once and caches it

Saves using the configured storage method

🚀 Example Usage in main()
cpp
Copy
Edit
editor->addText("Hello, world!");
editor->addNewLine();
editor->addText("This is a real-world document editor example.");
editor->addNewLine();
editor->addTabSpace();
editor->addText("Indented text after a tab space.");
editor->addNewLine();
editor->addImage("picture.jpg");
Output:

pgsql
Copy
Edit
Hello, world!
This is a real-world document editor example.
	Indented text after a tab space.
[Image: picture.jpg]
This output also gets saved to document.txt.

✅ Key Features Demonstrated
Feature	Description
Polymorphism	DocumentElement* allows flexible rendering of different element types
Abstraction	Base classes DocumentElement and Persistence
Separation of Concerns	Rendering, data modeling, and storage are separated
Extensibility	Easy to add new element types (e.g., bold text, headers) or new storage methods
Reusability	Logic is modular and reusable in larger systems

📌 Summary
This code represents a clean, extensible object-oriented document editor framework. It's an excellent example of how to:

Use design patterns and principles

Build a modular architecture

Separate UI (text), data (document), and persistence (saving)
***/
