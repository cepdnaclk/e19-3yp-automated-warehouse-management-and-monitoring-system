import {
  Grid,
  GridItem,
  Button,
  Flex,
  Spacer,
  Select,
  List,
} from "@chakra-ui/react";
import { Image } from "@chakra-ui/react";
import logo from "/img/LOGO.png";
import { Avatar, AvatarBadge, AvatarGroup } from "@chakra-ui/react";
import { ChevronDownIcon } from "@chakra-ui/icons";
import { useEffect } from "react";
import axios from "axios";
import { Link } from "react-router-dom";
import {
  Modal,
  ModalOverlay,
  ModalContent,
  ModalHeader,
  ModalCloseButton,
  ModalBody,
  ModalFooter,
  FormControl,
  FormLabel,
  Input,
  NumberInput,
  NumberInputField,
} from "@chakra-ui/react";
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
} from "@chakra-ui/react";
import { AiOutlineUser } from "react-icons/ai";

import "../../css/gridItem.css";
import "../../css/palletJackList.css";
import "../../css/adminLayout.css";

import EmployeeData from "../../components/EmployeesData";
import ListItem from "../../components/ListItem";

export default function Admin() {
  const clientId = "emqx_react_" + Math.random().toString(16).substring(2, 8);
  const username = "emqx_test";
  const password = "emqx_test";
  const topic = "esp8266/test";
  const client = mqtt.connect("ws://broker.emqx.io:8083/mqtt", {
  clientId,
  username,
  password,
  });
  // const mqttSub = (subscription) => {
  //   if (client) {
  //     const { topic, qos } = subscription
  //     client.subscribe(topic, { qos }, (error) => {
  //       if (error) {
  //         console.log('Subscribe to topics error', error)
  //         return
  //       }
  //       console.log(`Subscribe to topics: ${topic}`)
  //       setIsSub(true)
  //     })
  //   }
  // }
  const [selectedEmployee, setSelectedEmployee] = useState(null);
  const [isEmployeesOpen, setIsEmployeesOpen] = useState(false);
  const [isCreateMapOpen, setIsCreateMapOpen] = useState(false);
  const [isAddPalletOpen, setIsAddPalletOpen] = useState(false);
  const onCloseEmployees = () => setIsEmployeesOpen(false);
  const onCloseCreateMap = () => setIsCreateMapOpen(false);
  const onOpenEmployees = () => setIsEmployeesOpen(true);
  const onOpenCreateMap = () => setIsCreateMapOpen(true);
  const onCloseAddPallet = () => setIsAddPalletOpen(false);
  const onOpenAddPallet = () => setIsAddPalletOpen(true);
  const [selectedItem, setSelectedItem] = useState("");
  useEffect(() => {
    axios
      .get("https://your-aws-server.com/api/employees") // Replace with your actual API endpoint
      .then((response) => {
        setEmployees(response.data);
      })
      .catch((error) => {
        console.error("There was an error!", error);
      });
  }, []);

  return (
    <Grid
      templateAreas={`"header header"
                  "nav main"`}
      gridTemplateRows={"50px 1fr"}
      gridTemplateColumns={"2fr 1fr"}
      h="100vh"
      color="blackAlpha.700"
      fontWeight="bold"
    >
      <GridItem
        className="modal"
        pl="2"
        pr="2"
        bg="#140d07"
        area={"header"}
        paddingTop="0.2rem"
      >
        <Flex alignItems="center">
          <Link to="/dashboard">
            <Image src={logo} alt="Logo" boxSize="60px" marginTop="-0.2rem" />
          </Link>
          <Spacer />
          <Button colorScheme="teal" mr="2" onClick={onOpenCreateMap}>
            Change Map
          </Button>
          <Button colorScheme="teal" mr="2" onClick={onOpenAddPallet}>
            Add a Pallet
          </Button>
          <Button colorScheme="teal" mr="2" onClick={onOpenEmployees}>
            Employee Details
          </Button>
          <Modal isOpen={isEmployeesOpen} onClose={onCloseEmployees}>
            <ModalOverlay className="modalFileter" />
            <ModalContent>
              <ModalHeader>Employees</ModalHeader>
              <ModalCloseButton />
              <ModalBody>
                <EmployeeData />
              </ModalBody>
              <ModalFooter>
                <Button colorScheme="teal" mr={3} onClick={onCloseEmployees}>
                  Cancel
                </Button>
              </ModalFooter>
            </ModalContent>
          </Modal>
          <Modal isOpen={isAddPalletOpen} onClose={onCloseAddPallet}>
                        <ModalOverlay className="modalFileter" />

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
              >
                Add Pallet
              </ModalHeader>
              <ModalCloseButton />
              <ModalBody>
                <FormControl>
                  <FormLabel>Pallet ID</FormLabel>
                  <NumberInput className = 'inputForms' min={0}>
                    <NumberInputField />
                  </NumberInput>
                </FormControl>
              </ModalBody>

              <ModalFooter>
                <Button colorScheme="teal" mr={3} onClick={onCloseCreateMap}>
                  Save
                </Button>
                <Button variant="ghost" onClick={onCloseCreateMap}>
                  Cancel
                </Button>
              </ModalFooter>
            </ModalContent>
          </Modal>
          <Modal isOpen={isCreateMapOpen} onClose={onCloseCreateMap}>
                        <ModalOverlay className="modalFileter" />

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
              >
                Create Map
              </ModalHeader>
              <ModalCloseButton />
              <ModalBody>
                <FormControl>
                  <FormLabel>Length</FormLabel>
                  <NumberInput className = 'inputForms' min={0}>
                    <NumberInputField />
                  </NumberInput>

                  <FormLabel>Width</FormLabel>
                  <NumberInput className = 'inputForms' min={0}>
                    <NumberInputField />
                  </NumberInput>

                  <FormLabel>Image</FormLabel>
                  <Input className = 'inputFormsImg' type="file" />

                  <FormLabel>Block Numbers</FormLabel>
                  <NumberInput className = 'inputForms' min={0}>
                    <NumberInputField />
                  </NumberInput>
                </FormControl>
              </ModalBody>

              <ModalFooter>
                <Button colorScheme="teal" mr={3} onClick={onCloseCreateMap}>
                  Save
                </Button>
                <Button variant="ghost" onClick={onCloseCreateMap}>
                  Cancel
                </Button>
              </ModalFooter>
            </ModalContent>
          </Modal>
          <Menu>
            <MenuButton
              as={Avatar}
              rightIcon={<ChevronDownIcon />}
              marginLeft="1rem"
              marginRight="1rem"
            ></MenuButton>
            <MenuList>
              <MenuItem>Log Out</MenuItem>
            </MenuList>
          </Menu>
        </Flex>
      </GridItem>
      <GridItem className="gridItem" area={"nav"}>
        <div className="gridItemDiv">
          <img src="/img/Map.jpeg" alt="logo" className="gridItemImg" />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack1"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack2"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack3"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack4"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack5"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack6"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack7"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack8"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack9"
          />
          <img
            src="/img/locationTag.png"
            alt="logo"
            className="gridItemImgLocation palletJack10"
          />
        </div>
      </GridItem>
      {/* <GridItem bg='#140d07' area={'main'}>
  <Select placeholder="Select option" onChange={(e) => setSelectedItem(e.target.value)} paddingTop="3rem">
    {employees.map((employee) => (
      <option key={employee.id} value={employee.name}>
        {employee.name}
      </option>
    ))}
  </Select>
  {selectedItem && <div>Selected Item: {selectedItem}</div>}
</GridItem> */}
      <GridItem
        padding={"20px"}
        paddingTop={"40px"}
        h={"100%"}
        bg="#140d07"
        area={"main"}
      >
        <div className="PJListMainContainer">
          <div className="PJListHeader">
            <h1>Pallet Jacks</h1>
          </div>
          <div className="PJListContainer">
            <ListItem />
          </div>
        </div>
      </GridItem>
    </Grid>
  );
}
