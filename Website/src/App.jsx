import { 
  createBrowserRouter, 
  createRoutesFromElements, 
  Route, 
  RouterProvider 
} from 'react-router-dom'
import { ChakraProvider } from '@chakra-ui/react';
import {Amplify} from 'aws-amplify';

// layouts and pages
import RootLayout from './layouts/RootLayout'
import Dashboard from './pages/Dashboard'
import User from './pages/User'
import Admin from './pages/Admin'


// router and routes
const router = createBrowserRouter(
  createRoutesFromElements(
      <Route path="/" element={<RootLayout />}>
      <Route path="dashboard" element={<Dashboard />} />
      <Route index element={<Dashboard />} />
      <Route path="user" element={<User />} />
      <Route path="admin" element={<Admin />} />
    </Route>
  )
)

function App() {
  return (
    <ChakraProvider>
    <RouterProvider router={router} />
    </ChakraProvider>
  )
}

export default App
