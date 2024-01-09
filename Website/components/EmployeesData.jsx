import React, { useEffect, useState } from 'react';
import { API_BASE_URL } from '../src/config';
import "../css/employeeStyles.css";
import io from 'socket.io-client';

function EmployeeData(props) {
  const [employees, setEmployee] = useState([]);
  useEffect(() => {
    const socket = io(API_BASE_URL);

    socket.on('employees', (data) => {
      setEmployee(data);
    });

    return () => {
      socket.disconnect();
    };
  }, []);
  return (
    <div className="listContainer">
      <ul className="scrollableList">
        {employees.map((employee) => (
          <li key={employee.id}>
            <div className="employee-item">
              <p>Employee ID: {employee.userId}</p>
              <p>Employee Name: {employee.username}</p>
              <p>Email: {employee.email}</p>
              <p>Contact Number: {employee.phoneNumber}</p>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default EmployeeData;
