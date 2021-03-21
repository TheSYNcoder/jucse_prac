import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Employee
{
    String code;
    String name;
    int salary;
    String grade;
    String dept_code;

    public Employee(String code, String name, int salary, String grade, String dept_code) {
        this.code = code;
        this.name = name;
        this.salary = salary;
        this.grade = grade;
        this.dept_code = dept_code;
    }

    @Override
    public String toString() {
        return "{" +
            " code='" + getCode() + "'" +
            ", name='" + getName() + "'" +
            ", salary='" + getSalary() + "'" +
            ", grade='" + getGrade() + "'" +
            ", dept_code='" + getDept_code() + "'" +
            "}";
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

    public int getSalary() {
        return this.salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    public String getGrade() {
        return this.grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }

    public String getDept_code() {
        return this.dept_code;
    }

    public void setDept_code(String dept_code) {
        this.dept_code = dept_code;
    }

}


class EmployeeList{
    Employee[] employeeList;
    int number_of_employees;
    Map<String,String> dept_name_to_code;

    EmployeeList(){
        this.employeeList = new Employee[1000];
        this.number_of_employees = 0 ;
        dept_name_to_code = new HashMap<>();
        dept_name_to_code.put("Management" , "001");
        dept_name_to_code.put("Business" , "002");
        dept_name_to_code.put("Engineering" , "003");
        dept_name_to_code.put("HR" , "004");
        dept_name_to_code.put("Marketing" , "005");
    }

    Boolean check_unique(String code){
        for ( int i = 0;  i < this.number_of_employees ; i++ ){
            if ( employeeList[i].getCode().equals(code))
                return false;
        }
        return true;
    }

    String get_code(String department){
        return dept_name_to_code.get(department);
    }

    int curr(){
        return number_of_employees;
    }

    void add(Employee e){
        employeeList[number_of_employees++] = e;
    }

    Employee get_details( String code){
        for ( int i = 0;  i < number_of_employees ; i++ ){
            if ( employeeList[i].getCode().equals(code))
                return employeeList[i];
        }
        return null;   
    }

    


}


class GUI{
    private JFrame mainframe;
    private JTabbedPane tabbedPane;
    EmployeeList list;
    private JTextField addName;
    private JTextField addCode;
    private JTextField addSalary;
    private JTextField searchCode;
    private ButtonGroup bg;
    JComboBox<String> cb;
    private JPanel searchQ;
    
    

    public GUI(){
        list = new EmployeeList();
        
        prepareGUI();
        
    }

    private void prepareGUI(){
        mainframe = new JFrame("Employee Records");
        mainframe.setSize( 700 , 300 );
        tabbedPane = new JTabbedPane();

        JComponent panel1 = makeAdding();  
        tabbedPane.addTab("Add", null , panel1,
                "Does nothing");
        tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
        JComponent panel2 = makeSearch();
        tabbedPane.addTab("Search", null , panel2,
                "Does twice as much nothing");
        tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);
        tabbedPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
        mainframe.add( tabbedPane);
        mainframe.setVisible(true);

    }

    protected JComponent makeTextPanel(String text) {
        JPanel panel = new JPanel(false);
        JLabel filler = new JLabel(text);
        filler.setHorizontalAlignment(JLabel.CENTER);
        panel.setLayout(new GridLayout(1, 1));
        panel.add(filler);
        return panel;
    }

    private JComponent makeSearch(){
        JPanel panel = new JPanel(false);
        JLabel label = new JLabel("Enter Employee Code");
        panel.add(label);
        searchCode = new JTextField(20);
        
        
        panel.add(searchCode);
        JLabel detaillab = new JLabel("INIT");
        detaillab.setVisible(false);
        panel.add(detaillab);
        JButton search = new JButton("Search");
        search.addActionListener( e -> {
            String code = searchCode.getText();
            Employee emp = list.get_details(code);
            if (emp != null){
                String details ="\nEmployee name:" + emp.getName() + "\nEmployee code:" + emp.getCode() +  "\nEmployee salary:" + emp.getSalary() + "\nEmployee grade:" + emp.getGrade()  +"\nEmployee department code:" + emp.getDept_code() ;        
                detaillab.setText(details);
                detaillab.setVisible(true);
            }
        });
        panel.add(search);
        return panel;
    }

    private JComponent makeAdding(){
        JPanel panel= new JPanel(false);
        // GridLayout layout = new GridLayout( 2, 3);
        // panel.setLayout(layout);
        JComponent name = createLabelTextField("Employee Name");
        panel.add(name);
        JComponent code = createLabelTextField("Employee Code");
        panel.add(code);
        JComponent salary = createLabelTextField("Employee Basic Salary");
        panel.add(salary);
        // JComponent cod = createLabelTextField("Employee Code");
        // panel.add(cod);
        

        JComponent radio = createRadio();
        panel.add(radio);
        JComponent drop = createDrop();
        panel.add(drop);
        JButton save = new JButton("SAVE");
        save.addActionListener( e -> {
            String nameT = addName.getText();
            String codeT = addCode.getText();
            String salaryT = addSalary.getText();
            int sal = Integer.parseInt(salaryT);
            String grade = bg.getSelection().getActionCommand();
            String dept = cb.getItemAt(cb.getSelectedIndex());  
            String deptCode = list.get_code(dept);
            if (list.check_unique(codeT)== false){
                JOptionPane.showMessageDialog(mainframe,"Employee code should be unique.","Alert",JOptionPane.WARNING_MESSAGE);
                return;
            }
            Employee emp = new Employee(codeT , nameT , sal , grade , deptCode );
            String details ="\nEmployee name:" + nameT + "\nEmployee code:" + codeT +  "\nEmployee salary:" + salaryT + "\nEmployee grade:" + grade + "\nEmployee dept:" + dept +"\nEmployee department code:" + deptCode ;        
            int a=JOptionPane.showConfirmDialog(mainframe,"Are you sure you want to save?\n"+details);  
            if (a == JOptionPane.YES_OPTION)
                list.add(emp);

        });
        panel.add(save);
        return panel;

    }

    private JComponent createLabelTextField(String label){
        JPanel panel= new JPanel(false);
        panel.setLayout(new GridLayout(1, 2));
        JLabel lab = new JLabel(label);
        panel.add(lab);
        if ( label.equals("Employee Name")){
            addName = new JTextField(20);
            panel.add(addName);
        }
        else if ( label.equals("Employee Code")){
            addCode = new JTextField(20);
            panel.add(addCode);
        }
        else{
            addSalary = new JTextField(20);
            panel.add(addSalary);
        }
        return panel;
    }

    private JComponent createRadio(){
        JPanel panel = new JPanel(false);
        panel.setLayout(new GridLayout(1,3));
        JLabel label = new JLabel("Employee Grade :");
        JRadioButton r1 = new JRadioButton("Grade A");
        JRadioButton r2 = new JRadioButton("Grade B");
        JRadioButton r3 = new JRadioButton("Grade C");
        r1.setActionCommand("A");
        r2.setActionCommand("B");
        r3.setActionCommand("C");
        // ButtonGroup bg = new ButtonGroup();
        bg = new ButtonGroup();
        bg.add(r1);bg.add(r2);
        bg.add(r3);
        panel.add(label);
        panel.add( r1);
        panel.add(r2);
        panel.add(r3);
        return panel;
    }

    private JComponent createDrop(){
        JPanel panel = new JPanel(false);
        JLabel label = new JLabel("Select department");
        panel.add(label);
        String[] depts = {"Management" , "Business" , "Marketing" , "HR", "Engineering"};
        cb = new JComboBox<String>(depts);
        panel.add(cb);
        return panel;

    }

    public static void main(String[] args){
        GUI gui = new GUI();
    }
}