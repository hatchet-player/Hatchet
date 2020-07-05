// TODO: find a way to enumerate TypeInfo instead of copying this manually
Hatchet.InfoSystem = Hatchet.InfoSystem || {};
Hatchet.InfoSystem.InfoType = Object.create(null);

Hatchet.InfoSystem.InfoType.InfoNoInfo = 0; //WARNING: *ALWAYS* keep this first!
Hatchet.InfoSystem.InfoType.InfoTrackID = 1;
Hatchet.InfoSystem.InfoType.InfoTrackArtist = 2;
Hatchet.InfoSystem.InfoType.InfoTrackAlbum = 3;
Hatchet.InfoSystem.InfoType.InfoTrackGenre = 4;
Hatchet.InfoSystem.InfoType.InfoTrackComposer = 5;
Hatchet.InfoSystem.InfoType.InfoTrackDate = 6;
Hatchet.InfoSystem.InfoType.InfoTrackNumber = 7;
Hatchet.InfoSystem.InfoType.InfoTrackDiscNumber = 8;
Hatchet.InfoSystem.InfoType.InfoTrackBitRate = 9;
Hatchet.InfoSystem.InfoType.InfoTrackLength = 10;
Hatchet.InfoSystem.InfoType.InfoTrackSampleRate = 11;
Hatchet.InfoSystem.InfoType.InfoTrackFileSize = 12;
Hatchet.InfoSystem.InfoType.InfoTrackBPM = 13;
Hatchet.InfoSystem.InfoType.InfoTrackReplayGain = 14;
Hatchet.InfoSystem.InfoType.InfoTrackReplayPeakGain = 15;
Hatchet.InfoSystem.InfoType.InfoTrackLyrics = 16;
Hatchet.InfoSystem.InfoType.InfoTrackLocation = 17;
Hatchet.InfoSystem.InfoType.InfoTrackProfile = 18;
Hatchet.InfoSystem.InfoType.InfoTrackEnergy = 19;
Hatchet.InfoSystem.InfoType.InfoTrackDanceability = 20;
Hatchet.InfoSystem.InfoType.InfoTrackTempo = 21;
Hatchet.InfoSystem.InfoType.InfoTrackLoudness = 22;
Hatchet.InfoSystem.InfoType.InfoTrackSimilars = 23; // cached -- do not change

Hatchet.InfoSystem.InfoType.InfoArtistID = 25;
Hatchet.InfoSystem.InfoType.InfoArtistName = 26;
Hatchet.InfoSystem.InfoType.InfoArtistBiography = 27;
Hatchet.InfoSystem.InfoType.InfoArtistImages = 28; //cached -- do not change
Hatchet.InfoSystem.InfoType.InfoArtistBlog = 29;
Hatchet.InfoSystem.InfoType.InfoArtistFamiliarity = 30;
Hatchet.InfoSystem.InfoType.InfoArtistHotttness = 31;
Hatchet.InfoSystem.InfoType.InfoArtistSongs = 32; //cached -- do not change
Hatchet.InfoSystem.InfoType.InfoArtistSimilars = 33; //cached -- do not change
Hatchet.InfoSystem.InfoType.InfoArtistNews = 34;
Hatchet.InfoSystem.InfoType.InfoArtistProfile = 35;
Hatchet.InfoSystem.InfoType.InfoArtistReviews = 36;
Hatchet.InfoSystem.InfoType.InfoArtistTerms = 37;
Hatchet.InfoSystem.InfoType.InfoArtistLinks = 38;
Hatchet.InfoSystem.InfoType.InfoArtistVideos = 39;
Hatchet.InfoSystem.InfoType.InfoArtistReleases = 40;

Hatchet.InfoSystem.InfoType.InfoAlbumID = 42;
Hatchet.InfoSystem.InfoType.InfoAlbumCoverArt = 43; //cached -- do not change
Hatchet.InfoSystem.InfoType.InfoAlbumName = 44;
Hatchet.InfoSystem.InfoType.InfoAlbumArtist = 45;
Hatchet.InfoSystem.InfoType.InfoAlbumDate = 46;
Hatchet.InfoSystem.InfoType.InfoAlbumGenre = 47;
Hatchet.InfoSystem.InfoType.InfoAlbumComposer = 48;
Hatchet.InfoSystem.InfoType.InfoAlbumSongs = 49;
Hatchet.InfoSystem.InfoType.InfoAlbumPurchaseUrl = 50;

Hatchet.InfoSystem.InfoType.InfoChartCapabilities = 60;

Hatchet.InfoSystem.InfoType.InfoChart = 61;

Hatchet.InfoSystem.InfoType.InfoNewReleaseCapabilities = 62;
Hatchet.InfoSystem.InfoType.InfoNewRelease = 63;

Hatchet.InfoSystem.InfoType.InfoMiscTopHotttness = 70;
Hatchet.InfoSystem.InfoType.InfoMiscTopTerms = 71;

Hatchet.InfoSystem.InfoType.InfoSubmitNowPlaying = 80;
Hatchet.InfoSystem.InfoType.InfoSubmitScrobble = 81;

Hatchet.InfoSystem.InfoType.InfoNowPlaying = 90;
Hatchet.InfoSystem.InfoType.InfoNowPaused = 91;
Hatchet.InfoSystem.InfoType.InfoNowResumed = 92;
Hatchet.InfoSystem.InfoType.InfoNowStopped = 93;
Hatchet.InfoSystem.InfoType.InfoTrackUnresolved = 94;

Hatchet.InfoSystem.InfoType.InfoLove = 100;
Hatchet.InfoSystem.InfoType.InfoUnLove = 101;
Hatchet.InfoSystem.InfoType.InfoShareTrack = 102;

Hatchet.InfoSystem.InfoType.InfoNotifyUser = 110;

Hatchet.InfoSystem.InfoType.InfoInboxReceived = 111;

Hatchet.InfoSystem.InfoType.InfoLastInfo = 112; //WARNING: *ALWAYS* keep this last!

// PushInfoFlags
Hatchet.InfoSystem.PushInfoFlags = Object.create(null);
Hatchet.InfoSystem.PushInfoFlags.PushNoFlag = 1;
Hatchet.InfoSystem.PushInfoFlags.PushShortUrlFlag = 2;

Hatchet.InfoSystem.InfoPlugin = {
    infoTypeString: function (infoType) {
        for (var currentInfoTypeString in Hatchet.InfoSystem.InfoType) {
            if (Hatchet.InfoSystem.InfoType[currentInfoTypeString] === infoType) {
                return currentInfoTypeString;
            }
        }
    },
    _notInCache: function (params) {
        return this.notInCache(params.type, params.criteria);
    },
    notInCache: function (infoType, criteria) {
        var requestMethod = 'request' + this.infoTypeString(infoType);

        return RSVP.Promise.resolve(this[requestMethod](criteria));
    },
    pushInfo: function (pushData) {
        var pushMethod = 'push' + this.infoTypeString(pushData.type);
        return this[pushMethod](pushData);
    },
    _getInfo: function (params) {
        return this.getInfo(params.type, params.data);
    },
    getInfo: function (type, infoHash) {
        var getInfoMethod = 'get' + this.infoTypeString(type);

        return RSVP.Promise.resolve(this[getInfoMethod](infoHash));
    }
};
