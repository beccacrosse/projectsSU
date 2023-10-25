import { useState, useEffect } from "react";
import getEnv from "./env";

import { getMyTopTracks, getAlbumTracks } from "./apiOptions";

const { ALBUM_ID } = getEnv();

const useSpotifyTracks = (token) => {
  // TODO: implement this!
};

export default useSpotifyTracks;
