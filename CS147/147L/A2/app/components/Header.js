import { StyleSheet, View, Text, Image, Dimensions } from "react-native";
import Icons from "../../assets/Icons";

const windowWidth = Dimensions.get("window").width;
const windowHeight = Dimensions.get("window").height;

const Header = () => {
  const isTablet = (windowWidth > 500)
  return (
    <View style={isTablet ? [styles.header, styles.headerTablet]
      : styles.header}>
      <Image source={Icons.menu.light} style={isTablet ? styles.headerIconsTablet
    : styles.headerIcons} />
      <Text style={styles.title}>Hinj</Text>
      <Image source={Icons.sun} style={isTablet ? styles.headerIconsTablet
    : styles.headerIcons} />
    </View>
  );
};

const styles = StyleSheet.create({
  headerIcons: {
    height: windowWidth * 0.15,
    width: windowWidth * 0.15,
  },
  headerIconsTablet: {
    height: windowWidth * 0.1,
    width: windowWidth * 0.1,
  },
  title: {
    fontFamily: "Sydney-Bold",
    fontSize: (windowWidth/10.83),
    color: Themes.light.text
  },
  header: {
    paddingVertical:  windowWidth * 0.1,
    width: "100%",
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
  },
  headerTablet: {
    paddingBottom:windowWidth * 0.05
  }
});

export default Header;
