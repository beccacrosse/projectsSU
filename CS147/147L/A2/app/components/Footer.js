import {
  StyleSheet,
  Text,
  View,
  Image,
  Dimensions,
  PixelRatio,
} from "react-native";
import * as Device from 'expo-device';
import { Icons, Themes } from "../../assets/Themes";

// advanced JS syntax: destructure and rename variables
const { height: windowHeight, width: windowWidth } = Dimensions.get("window");

const Footer = () => {
  return (
    <View style={styles.navigationContainer}>
      <View style={styles.pair}>
        <Image source={Icons.discover.light} style={styles.icons} />
        <Text style={styles.text}>Discover</Text>
      </View>
      <View style={styles.pair}>
        <Image source={Icons.heart.light} style={styles.icons} />
        <Text style={styles.text} >Matches</Text>
      </View>
      <View style={styles.pair}>
        <Image source={Icons.messages.light} style={styles.icons} />
        <Text style={styles.text}>Discover</Text>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  navigationContainer: {
    padding: 10,
    borderWith: 5,
    flexDirection: "row",
    justifyContent: "space-around",
    backgroundColor: Themes.light.navigation,
    width: windowWidth,
    height: windowHeight * 0.1, // Alternatively, use the `flex` style
  },
  pair : {
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center"
  },
  icons : {
    height: windowHeight * 0.05,
    aspectRatio: 1,
  },
  text : {
    color: Themes.light.bgSecondary,
    fontSize: 14
  }
});

export default Footer;
