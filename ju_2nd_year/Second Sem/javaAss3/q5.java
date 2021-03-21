import java.util.*;
import java.io.*;

class Student implements Serializable{
    int roll;
    String name;
    int score;


    public Student() {
    }

    public Student(int roll, String name, int score) {
        this.roll = roll;
        this.name = name;
        this.score = score;
    }

    public int getRoll() {
        return this.roll;
    }

    public void setRoll(int roll) {
        this.roll = roll;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getScore() {
        return this.score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public Student roll(int roll) {
        this.roll = roll;
        return this;
    }

    public Student name(String name) {
        this.name = name;
        return this;
    }

    public Student score(int score) {
        this.score = score;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Student)) {
            return false;
        }
        Student student = (Student) o;
        return roll == student.roll && Objects.equals(name, student.name) && score == student.score;
    }

    @Override
    public int hashCode() {
        return Objects.hash(roll, name, score);
    }

    @Override
    public String toString() {
        return "{" +
            " roll='" + getRoll() + "'" +
            ", name='" + getName() + "'" +
            ", score='" + getScore() + "'" +
            "}";
    }



}

class Test{

    public static void main(String args[]){
        Student a = new Student(1 , "name1" , 34);
        Student b = new Student(2 , "name1" , 34);
        try{
        FileOutputStream f1 = new FileOutputStream("student.bin");
        ObjectOutputStream f2 = new ObjectOutputStream(f1);
        f2.writeObject(a);
        f2.writeObject(b);
        f2.close();
        f2.close();

        FileInputStream ff1 = new FileInputStream("student.bin");
        ObjectInputStream ff2 = new ObjectInputStream(ff1);
        System.out.println((Student) ff2.readObject());
        System.out.println((Student) ff2.readObject());
        ff2.close();
        ff1.close();

        }
        catch(FileNotFoundException  e){
            System.out.println(e);
        }
        catch(IOException e){
            System.out.println(e);
        }
        catch( ClassNotFoundException e){
            System.err.println(e);
        }

    }
}