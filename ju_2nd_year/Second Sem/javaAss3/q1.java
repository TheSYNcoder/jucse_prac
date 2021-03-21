import java.util.*;

class Department{
    String code;
    String location;
    String name;



    public Department() {
    }

    public Department(String code, String location, String name) {
        this.code = code;
        this.location = location;
        this.name = name;
    }

    public String getCode() {
        return this.code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getLocation() {
        return this.location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Department code(String code) {
        this.code = code;
        return this;
    }

    public Department location(String location) {
        this.location = location;
        return this;
    }

    public Department name(String name) {
        this.name = name;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Department)) {
            return false;
        }
        Department department = (Department) o;
        return Objects.equals(code, department.code) && Objects.equals(location, department.location) && Objects.equals(name, department.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(code, location, name);
    }

    @Override
    public String toString() {
        return "{" +
            " code='" + getCode() + "'" +
            ", location='" + getLocation() + "'" +
            ", name='" + getName() + "'" +
            "}";
    }

    public void getData(String code){
        Scanner sc = new Scanner(System.in);
        // System.out.println("Enter departmenrt code");
        // String code = sc.nextLine();
        System.out.println("Enter department location");
        String location = sc.nextLine();
        System.out.println("Enter department name");
        String name = sc.nextLine();
        setName(name);
        setCode(code);
        setLocation(location);
    }


    void display(){
        System.out.println(this);
    }


}


class Employee{
    String code;
    String name;
    int basic;
    String dept_code;

    public Employee() {
    }

    public Employee(String code, String name, int basic, String dept_code) {
        this.code = code;
        this.name = name;
        this.basic = basic;
        this.dept_code = dept_code;
    }

    public String getCode() {
        return this.code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getBasic() {
        return this.basic;
    }

    public void setBasic(int basic) {
        this.basic = basic;
    }

    public String getDept_code() {
        return this.dept_code;
    }

    public void setDept_code(String dept_code) {
        this.dept_code = dept_code;
    }

    public Employee code(String code) {
        this.code = code;
        return this;
    }

    public Employee name(String name) {
        this.name = name;
        return this;
    }

    public Employee basic(int basic) {
        this.basic = basic;
        return this;
    }

    public Employee dept_code(String dept_code) {
        this.dept_code = dept_code;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Employee)) {
            return false;
        }
        Employee employee = (Employee) o;
        return Objects.equals(code, employee.code) && Objects.equals(name, employee.name) && basic == employee.basic && Objects.equals(dept_code, employee.dept_code);
    }

    @Override
    public int hashCode() {
        return Objects.hash(code, name, basic, dept_code);
    }

    @Override
    public String toString() {
        return "{" +
            " code='" + getCode() + "'" +
            ", name='" + getName() + "'" +
            ", basic='" + getBasic() + "'" +
            ", dept_code='" + getDept_code() + "'" +
            "}";
    }

    public void getData(String code){
        Scanner sc = new Scanner(System.in);
        // System.out.print("Enter departmenrt code\n");
        // String code = sc.nextLine();
        System.out.print("Enter department name\n");
        String name = sc.nextLine();
        System.out.print("Enter department basic\n");
        int basic = sc.nextInt();
        System.out.print("Enter department Dept code\n");
        String dummy = sc.nextLine();
        String dept_code = sc.nextLine();
        setName(name);
        setBasic(basic);
        setCode(code);
        setDept_code(dept_code);
    }

    public void show()
    {
        System.out.println(this);
    }

}

class Dept_List{
    ArrayList<Department> arr;
    public Dept_List() {
        arr = new ArrayList<Department>();
    }
    void add(String code){
        Department d = new Department();
        for ( int i = 0 ; i < arr.size() ; i++ ){
            if ( arr.get(i).getCode().equals(code)){
                System.out.println("Not unique department");
            }
        }
        d.getData(code);
        arr.add(d);
    }

    void show( String code){
        for ( int  i = 0 ; i < arr.size() ; i ++ ){
            if ( arr.get(i).getCode().equals(code)){
                arr.get(i).display();
            }
        }
        System.out.println("Not found");
    }

    int calTotalPay(Emp_List e , String code){
        int f =0;
        for ( int i =0 ; i < arr.size() ; i ++ ){
            if ( arr.get(i).getCode().equals(code)){
                f = 1;
                break;
            }
        }
        if ( f == 0){
            System.out.println("wrong code");
            return -1;
        }
        int sum = 0;
        for ( int i = 0 ; i < e.arr.size() ; i++ ){
            if ( e.arr.get(i).getDept_code().equals(code)){
                sum += e.arr.get(i).getBasic();
            }
        }
        return sum;
    }
}

class SortByBasic implements Comparator<Employee>{

    public int compare(Employee e1 , Employee e2 ){
        return ( e2.basic - e1.basic );
}
}


class Emp_List{
    ArrayList<Employee> arr;
    public Emp_List(){
        arr = new ArrayList<Employee>();
    }

    void add(String code){
        Employee d = new Employee();
        for (int i = 0; i < arr.size(); i++) {
            if (arr.get(i).getCode().equals(code)) {
                System.out.println("Not unique");
            }
        }
        d.getData(code);
        arr.add(d);
    }

    void display( String code , Dept_List d){
        for ( int i = 0; i < arr.size() ; i++){
            if ( arr.get(i).getCode().equals(code) ){
                arr.get(i).show();
                d.show(arr.get(i).getDept_code());
                return ;
            }
        }
    }
    void displayAll(){
        for ( int i =0 ; i  < arr.size() ; i ++ ){
            System.out.println(arr.get(i));
        }
    }

    void remove( String code){
        for ( int i =0 ; i < arr.size() ; i++){
            if ( arr.get(i).getCode().equals(code)){
                arr.remove(i);
                return;
            }
        }
        System.out.println("Not present");
    }

    void modify( String code , int new_basic){
        for ( int i =0 ; i < arr.size() ; i++){
            if ( arr.get(i).getCode().equals(code)){
                arr.get(i).setBasic(new_basic);
                return;
            }
        }
        System.out.println("Not found");
    }

    void sort(){
        ArrayList<Employee> ar1 = new ArrayList<Employee>();
        for ( Employee e : arr){
            ar1.add(e);
        }
        Collections.sort(ar1 , new SortByBasic());
        for ( Employee e : ar1){
            System.out.println(e);
        }
    }
}



class Test{
     public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Emp_List e = new Emp_List();
        Dept_List d = new Dept_List();
        while(true){
            System.out.println("Menu Screen");
            System.out.println("1  to add employee");
            System.out.println("2 to add department");
            System.out.println("3 to display details of all departments");
            System.out.println("4 to find total basic pay for a department");
            System.out.println("5 to remove an employee by code");
            System.out.println("6 to sort employee");
            int choice = sc.nextInt();
            String code;
            String dummy;
            switch(choice)
            {
                case 1:
                    System.out.println("Enter employee code");
                    code = sc.next();
                    dummy = sc.nextLine();
                    e.add(code);
                    break;
                case 2:
                    System.out.println("Enter department code");
                    code = sc.next();
                     dummy = sc.nextLine();
                    d.add(code);
                    break;
                case 3:
                    e.displayAll();
                    break;
                case 4:
                {
                    System.out.print("Enter code\n");
                    String dum   = sc.nextLine();
                    
                    code = sc.nextLine();
                    
                    
                    System.out.println(d.calTotalPay(e, code));
                    break;
                }
                case 5:
                {
                    System.out.print("Enter code\n");
                    String dum = sc.nextLine();
                    code = sc.nextLine();
                    
                    e.remove(code);
                    break;
                }
                case 6:
                {
                    e.sort();
                    break;
                }
                default:
                    System.out.println("Wrong choice");
                    break;
            }
            

            System.out.println("Enter n to break");
            char c = sc.next().charAt(0);
            if ( c == 'n')
                break;
        }

     }
}
