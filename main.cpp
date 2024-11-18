#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>  // for setprecision

// Base class Student
class Student {
protected:
    std::string firstName;
    std::string lastName;
    double gpa;
    int gradYear;
    std::string gradSemester;
    int enrolledYear;
    std::string enrolledSemester;
    bool isUndergrad;

public:
    Student() {
        firstName = "Hunter";
        lastName = "Jackson";
        gpa = 3.0;
        gradYear = 2026;
        gradSemester = "Spring";
        enrolledYear = 2022;
        enrolledSemester = "Fall";
        isUndergrad = true;
    }

    virtual ~Student() {}

    // Getter methods
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    double getGPA() const { return gpa; }
    int getGradYear() const { return gradYear; }
    std::string getGradSemester() const { return gradSemester; }
    int getEnrolledYear() const { return enrolledYear; }
    std::string getEnrolledSemester() const { return enrolledSemester; }
    bool getIsUndergrad() const { return isUndergrad; }

    // Setter methods
    void setName(const std::string& first, const std::string& last) {
        firstName = first;
        lastName = last;
    }
    
    void setGPA(double g) { gpa = g; }
    void setGradYear(int year) { gradYear = year; }
    void setGradSemester(const std::string& sem) { gradSemester = sem; }
    void setEnrolledYear(int year) { enrolledYear = year; }
    void setEnrolledSemester(const std::string& sem) { enrolledSemester = sem; }
    void setIsUndergrad(bool isUG) { isUndergrad = isUG; }

    virtual void writeToFile(std::ofstream& outFile) const {
        outFile << "Name: " << firstName << " " << lastName << "\n"
                << "GPA: " << std::fixed << std::setprecision(2) << gpa << "\n"
                << "Graduation: " << gradSemester << " " << gradYear << "\n"
                << "Enrolled: " << enrolledSemester << " " << enrolledYear << "\n"
                << "Level: " << (isUndergrad ? "Undergraduate" : "Graduate") << "\n";
    }

    // Display method for console output
    virtual void display() const {
        std::cout << "Name: " << firstName << " " << lastName << "\n"
                  << "GPA: " << std::fixed << std::setprecision(2) << gpa << "\n"
                  << "Graduation: " << gradSemester << " " << gradYear << "\n"
                  << "Enrolled: " << enrolledSemester << " " << enrolledYear << "\n"
                  << "Level: " << (isUndergrad ? "Undergraduate" : "Graduate") << "\n";
    }
};

class Art_Student : public Student {
private:
    std::string artEmphasis;

public:
    Art_Student() : Student() {
        artEmphasis = "Art Studio";
    }

    std::string getArtEmphasis() const { return artEmphasis; }
    void setArtEmphasis(const std::string& emphasis) { artEmphasis = emphasis; }

    virtual void writeToFile(std::ofstream& outFile) const {
        outFile << "\nArt Student Information:\n";
        Student::writeToFile(outFile);
        outFile << "Art Emphasis: " << artEmphasis << "\n";
    }

    virtual void display() const {
        std::cout << "\nArt Student Information:\n";
        Student::display();
        std::cout << "Art Emphasis: " << artEmphasis << "\n";
    }
};

class Physics_Student : public Student {
private:
    std::string concentration;

public:
    Physics_Student() : Student() {
        concentration = "Biophysics";
    }

    std::string getConcentration() const { return concentration; }
    void setConcentration(const std::string& conc) { concentration = conc; }

    virtual void writeToFile(std::ofstream& outFile) const {
        outFile << "\nPhysics Student Information:\n";
        Student::writeToFile(outFile);
        outFile << "Concentration: " << concentration << "\n";
    }

    virtual void display() const {
        std::cout << "\nPhysics Student Information:\n";
        Student::display();
        std::cout << "Concentration: " << concentration << "\n";
    }
};

int main() {
    std::vector<Art_Student*> art_students;
    std::vector<Physics_Student*> physics_students;

    std::cout << "Creating student records...\n";

    // Create Art Students
    for(int i = 0; i < 5; i++) {
        Art_Student* art_student = new Art_Student();
        
        std::stringstream ss;
        ss << (i+1);
        std::string number = ss.str();
        
        art_student->setName("Art" + number, "Student" + number);
        art_student->setGPA(3.5 + (i * 0.1));
        art_student->setEnrolledYear(2020 + i);
        
        if(i % 3 == 0) art_student->setArtEmphasis("Art Studio");
        else if(i % 3 == 1) art_student->setArtEmphasis("Art History");
        else art_student->setArtEmphasis("Art Education");
        
        art_students.push_back(art_student);
    }

    // Create Physics Students
    for(int i = 0; i < 5; i++) {
        Physics_Student* physics_student = new Physics_Student();
        
        std::stringstream ss;
        ss << (i+1);
        std::string number = ss.str();
        
        physics_student->setName("Physics" + number, "Student" + number);
        physics_student->setGPA(3.7 + (i * 0.1));
        physics_student->setEnrolledYear(2020 + i);
        
        if(i % 2 == 0) physics_student->setConcentration("Biophysics");
        else physics_student->setConcentration("Earth and Planetary Sciences");
        
        physics_students.push_back(physics_student);
    }

    // Display to console
    std::cout << "\nDisplaying student information to console:\n";
    std::cout << "\nART STUDENTS\n=============\n";
    for(size_t i = 0; i < art_students.size(); ++i) {
        art_students[i]->display();
    }

    std::cout << "\nPHYSICS STUDENTS\n================\n";
    for(size_t i = 0; i < physics_students.size(); ++i) {
        physics_students[i]->display();
    }

    // Write to file
    std::ofstream outFile("student_info.dat");
    if(!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return 1;
    }
    
    outFile << "ART STUDENTS\n=============\n";
    for(size_t i = 0; i < art_students.size(); ++i) {
        art_students[i]->writeToFile(outFile);
    }

    outFile << "\nPHYSICS STUDENTS\n================\n";
    for(size_t i = 0; i < physics_students.size(); ++i) {
        physics_students[i]->writeToFile(outFile);
    }


    return 0;
}
