import { useState } from "react";
import "../css/employeeStyles.css";

function EmployeeData(props) {
  const [employees, setEmployee] = useState([
    {
      id: 1,
      name: "John Doe",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 2,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 3,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 4,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
      },
    {
      id: 1,
      name: "John Doe",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 2,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 3,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
    {
      id: 4,
      name: "Dasun Silva",
      contactEmail: "john.doe@example.com",
      contactPhone: "123-456-7890",
    },
  ]);

  return (
    <div className="listContainer">
      <ul className="scrollableList">
        {employees.map((employee) => (
          <li key={employee.id}>
            <div className="employee-item">
              <p>Employee ID: {employee.id}</p>
              <p>Employee Name: {employee.name}</p>
              <p>Email: {employee.contactEmail}</p>
              <p>Contact Number: {employee.contactPhone}</p>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default EmployeeData;
