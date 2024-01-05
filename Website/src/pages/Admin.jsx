import { Grid, GridItem, Button, Flex, Spacer } from '@chakra-ui/react'
import { Image } from '@chakra-ui/react'
import logo from '/img/LOGO.png'
import { Avatar, AvatarBadge, AvatarGroup } from '@chakra-ui/react'
import { ChevronDownIcon } from '@chakra-ui/icons'
import {useEffect } from 'react';
import axios from 'axios';
import { Link } from 'react-router-dom';
import { Modal, ModalOverlay, ModalContent, ModalHeader, ModalCloseButton, ModalBody, ModalFooter, FormControl, FormLabel, Input, NumberInput, NumberInputField } from "@chakra-ui/react";
import { useState } from "react";
import {
  Menu,
  MenuButton,
  MenuList,
  MenuItem,
  MenuItemOption,
  MenuGroup,
  MenuOptionGroup,
  MenuDivider,
} from '@chakra-ui/react'
import { AiOutlineUser } from 'react-icons/ai';



export default function Admin() {
  const [employees, setEmployees] = useState([]);
  const [selectedEmployee, setSelectedEmployee] = useState(null);
  const [isEmployeesOpen, setIsEmployeesOpen] = useState(false);
  const [isCreateMapOpen, setIsCreateMapOpen] = useState(false);
  const onCloseEmployees = () => setIsEmployeesOpen(false);
  const onCloseCreateMap = () => setIsCreateMapOpen(false);
  const onOpenEmployees = () => setIsEmployeesOpen(true);
  const onOpenCreateMap = () => setIsCreateMapOpen(true);
  useEffect(() => {
    axios.get('https://your-aws-server.com/api/employees') // Replace with your actual API endpoint
      .then(response => {
        setEmployees(response.data);
      })
      .catch(error => {
        console.error('There was an error!', error);
      });
  }, []);
  return (
  <Grid
  templateAreas={`"header header"
                  "nav main"`}
  gridTemplateRows={'50px 1fr'}
  gridTemplateColumns={'2fr 1fr'}
  h='100vh'
  color='blackAlpha.700'
  fontWeight='bold'
>
  <GridItem  pl='2' pr='2' bg='#140d07' area={'header'} paddingTop="0.2rem">
  <Flex alignItems="center">
  <Link to="/dashboard">
  <Image src={logo} alt="Logo" boxSize="60px" marginTop="-0.2rem"/>
</Link>
  <Spacer />
  <Button colorScheme="teal" mr="2"  onClick={onOpenEmployees}>
      Employees
    </Button>
    <Modal isOpen={isEmployeesOpen} onClose={onCloseEmployees}>
        <ModalOverlay />
        <ModalContent>
          <ModalHeader>Employees</ModalHeader>
          <ModalCloseButton />
          <ModalBody>
            {employees.map(employee => (
              <p key={employee.id} onClick={() => { setSelectedEmployee(employee); onClose(); }}>
                {employee.name}
              </p>
            ))}
             </ModalBody>
          <ModalFooter>
          <Button colorScheme="teal" mr={3} onClick={onCloseEmployees}>
 OK
</Button>
<Button variant="ghost" onClick={onCloseEmployees}>Cancel</Button>
          </ModalFooter>
        </ModalContent>
      </Modal>
      {selectedEmployee && (
        <div>
          <h2>{selectedEmployee.name}</h2>
          {/* Display other details of the selected employee */}
        </div>
      )}
    <Button colorScheme="teal">
      Pallet Jacks
    </Button>
    {/* <Spacer/> */}
    {/* <AvatarGroup marginLeft="1rem" marginRight="1rem" >
    <Avatar bg='red.500' icon={<AiOutlineUser fontSize='1.5rem' />} />
    <Avatar bg='teal.500' />
    </AvatarGroup> */}
    <Menu>
  <MenuButton as={Avatar} rightIcon={<ChevronDownIcon />} marginLeft="1rem" marginRight="1rem" >
  </MenuButton>
  <MenuList>
  <MenuItem onClick={onOpenCreateMap}>Create Map</MenuItem>

  <Modal isOpen={isCreateMapOpen} onClose={onCloseCreateMap}>
  <ModalOverlay />
  <ModalContent
  bg="white"
  color="black"
  borderRadius="8px"
  boxShadow="lg"
  maxW="400px"
  mx="auto"
  my="auto"
  >
    <ModalHeader
    bg="teal.500"
    color="white"
    p={4}
    fontSize="2xl"
    borderTopLeftRadius="8px"
    borderTopRightRadius="8px"
    >Create Map</ModalHeader>
    <ModalCloseButton />
    <ModalBody>
      <FormControl>
        <FormLabel>Length</FormLabel>
        <NumberInput min={0}>
          <NumberInputField />
        </NumberInput>

        <FormLabel>Width</FormLabel>
        <NumberInput min={0}>
          <NumberInputField />
        </NumberInput>

        <FormLabel>Image</FormLabel>
        <Input type="file" />

        <FormLabel>Block Numbers</FormLabel>
        <NumberInput min={0}>
          <NumberInputField />
        </NumberInput>
      </FormControl>
    </ModalBody>

    <ModalFooter>
    <Button colorScheme="teal" mr={3} onClick={onCloseCreateMap}>
  Save
</Button>
<Button variant="ghost" onClick={onCloseCreateMap}>Cancel</Button>
    </ModalFooter>
  </ModalContent>
</Modal>
    <MenuItem>Log Out</MenuItem>
  </MenuList>
</Menu>
  </Flex>

  </GridItem>
  <GridItem bg='#140d07' area={'nav'}>
  Nav
</GridItem>
  <GridItem  bg='#140d07' area={'main'}>
    Main
  </GridItem>
</Grid>
  )
}
