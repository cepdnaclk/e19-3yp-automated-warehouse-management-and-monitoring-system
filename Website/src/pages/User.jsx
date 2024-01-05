import { Grid, GridItem, Button, Flex, Spacer, MenuList, Avatar } from '@chakra-ui/react'
import { Image } from '@chakra-ui/react'
import logo from '/img/LOGO.png'
import {
  Menu,
  MenuButton,
  MenuItem,
  MenuGroup,
  MenuOptionGroup,
  MenuDivider,
} from '@chakra-ui/react'
import { ChevronDownIcon } from '@chakra-ui/icons'
import { Link } from 'react-router-dom'

export default function User() {
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
  <Spacer/>
  <Button colorScheme="teal">
      Pallet Jacks
  </Button>
    {/* <Spacer/> */}
    {/* <AvatarGroup marginLeft="1rem" marginRight="1rem" >
    <Avatar bg='red.500' icon={<AiOutlineUser fontSize='1.5rem' />} />
    <Avatar bg='teal.500' />
    </AvatarGroup> */}
  <Menu>
  <MenuButton as={Avatar} rightIcon={<ChevronDownIcon />} marginLeft="1rem" marginRight="1rem" />
  <MenuList>
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
