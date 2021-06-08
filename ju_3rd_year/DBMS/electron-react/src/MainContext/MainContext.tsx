import { createContext, Dispatch, useReducer } from "react";
import { APP_NAME } from "../constants";
import ActionTypes from "./ActionTypes";

export interface Department {
  name: string;
  deptCode: string;
}

export const isDepartment = (o: any): o is Department => {
  return o && "name" in o && "deptCode" in o;
};

export interface Student {
  roll: string;
  deptCode: string;
  name: string;
  address: string;
  phone: string;
}

export const isStudent = (o: any): o is Student => {
  return (
    o &&
    "roll" in o &&
    "deptCode" in o &&
    "name" in o &&
    "address" in o &&
    "phone" in o
  );
};

export interface State {
  name: string;
  students: Student[];
  departments: Department[];
}

export const isState = (o: any): o is State => {
  return o && "name" in o && "students" in o && "departments" in o;
};

export interface ContextAction {
  type: string;
  payload: any;
}

const initState: State = {
  name: APP_NAME,
  students: [
    { roll: "1", name: "test 1", deptCode: "CS", address: "NA", phone: "NA" },
    { roll: "2", name: "test 2", deptCode: "ECE", address: "NA", phone: "NA" },
    { roll: "3", name: "test 3", deptCode: "ME", address: "NA", phone: "NA" },
    { roll: "4", name: "test 4", deptCode: "CE", address: "NA", phone: "NA" },
    { roll: "5", name: "test 5", deptCode: "EE", address: "NA", phone: "NA" },
    { roll: "6", name: "test 6", deptCode: "CS", address: "NA", phone: "NA" },

  ],
  departments: [
    { deptCode: "CS", name: "Computer Science and Engineering" },
    { deptCode: "ECE", name: "Electronics Engineering" },
    { deptCode: "EE", name: "Electrical Engineering" },
    { deptCode: "ME", name: "Mechanical Engineering" },
    { deptCode: "CE", name: "Civil Engineering" },
  ],
};

const MainContext = createContext<{
  state: State;
  dispatch: Dispatch<ContextAction>;
}>({ state: initState, dispatch: () => null });

export const ContextReducer = (state: State, action: ContextAction): State => {
  switch (action.type) {
    case ActionTypes.ADD_STUDENT:
      // assumes already validated
      // payload is Student obj
      if (isStudent(action.payload)) {
        const st1: Student[] = [...state.students, action.payload];
        return { ...state, students: [...st1] };
      }
      return state;
    case ActionTypes.DELETE_STUDENT:
      // assumes already validated
      // payload is roll: string
      const st2: Student[] = state.students.filter(
        (student) => student.roll !== action.payload
      );
      return { ...state, students: [...st2] };
    case ActionTypes.EDIT_STUDENT:
      // assumes already validated
      // payload is Student obj
      if (isStudent(action.payload)) {
        const st3: Student[] = state.students.map((student) => {
          if (student.roll === action.payload.roll) {
            return action.payload;
          }
          return student;
        });
        return { ...state, students: [...st3] };
      }
      return state;
    default:
      return state;
  }
};

export const MainContextProvider = (props: any): JSX.Element => {
  const [state, dispatch] = useReducer(ContextReducer, initState);
  return (
    <MainContext.Provider value={{ state, dispatch }}>
      {props.children}
    </MainContext.Provider>
  );
};

export default MainContext;
