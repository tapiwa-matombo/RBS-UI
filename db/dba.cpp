#include "dba.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
/* 
  provides means of executing
 and manipulating SQl Statements
*/

DBA::DBA(QObject *parent )
    : QObject (parent)
{
   //Initialise database tables on start
}

QSqlError DBA::initDb()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(default_driver);
    db.setDatabaseName(default_dbname);
    if (!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return db.lastError();
    }
    else
    {
        QString q = "" ;
        qDebug() << "Database connected successfully";
        isActive = true;
        qDebug() << "Result of createMetaDataTable";
        foreach (QString q, tables()) {
           createMetaDataTable(q);
        }
        qDebug() << "return of .tables() function";
        qDebug() << db.tables().count();
    }
    return QSqlError();
}

//Get data from db
bool DBA::getResult(QString &q)
{
    QString stmt = "SELECT * FROM categories";
    q = stmt;
    QSqlQuery query;
    query.exec(q);
    QVariant v = query.result()->handle();
    if (v.isValid() && qstrcmp(v.typeName(), "sqlite3_stmt*") == 0)
    {
        //v.data() returns a pointer to the handle
//        sqlite3_stmt *handle = *static_cast<sqlite3_stmt **>(v.data());
    }
    qDebug() << v;
    return false;
}

// Query database
bool DBA::insert(QString &q)
{
   QString qs = q;
   return true;
}

// check if tables exist from database else create
QList<QString> DBA::tables()
{
    QSqlQuery query;
    QList<QString> tableList;
    //carts
    QString qCarts = "create table if not exists carts (ID int primary key,name varchar(40))";
    tableList.append(qCarts);
    QString iCarts = "INSERT INTO carts (ID, name) VALUES (1, 'Default')";
    tableList.append(iCarts);
    //carts_list
    QString qCartsList = "CREATE TABLE IF NOT EXISTS carts_list(ID int(11) primary key,"
                "pID int(11) NOT NULL,"
                "swID int(11) NOT NULL,"
                "swButton int(11) NOT NULL,"
                "color varchar(100) NOT NULL)";
    tableList.append(qCartsList);
    //category
    QString qCategory = "CREATE TABLE IF NOT EXISTS category("
               "ID int(11) primary key,"
                "name varchar(100) NOT NULL)";
    tableList.append(qCategory);
    QString iCategory = "INSERT INTO category (ID, name) VALUES"
            "(1, 'Music'),"
            "(2, 'Sound Effects'),"
            "(3, 'Sweepers'),"
            "(4, 'Station IDs'),"
            "(5, 'Jingles'),"
            "(6, 'Promos'),"
            "(7, 'Commercials'),"
            "(8, 'News'),"
            "(9, 'Interviews'),"
            "(10, 'Radio Shows'),"
            "(11, 'Radio Streams')";
    tableList.append(iCategory);
    //events
   QString qEvents = "CREATE TABLE IF NOT EXISTS events ("
      "ID int(11) primary key,"
      "type INT(2) NOT NULL,"
      "time varchar(20) NOT NULL,"
      " name varchar(200) NOT NULL,"
      " date date DEFAULT '2002-01-01',"
      "day varchar(30) DEFAULT '&',"
      "hours varchar(100) DEFAULT '&',"
      "data text,"
      "enabled BOOL DEFAULT '0',"
      "catID int(11) NOT NULL DEFAULT '0',"
      "smart INT(1) NOT NULL DEFAULT '0')";
   tableList.append(qEvents);
    //events_categories
   QString qEventsCategories = "CREATE TABLE IF NOT EXISTS events_categories ("
     "ID int(11) primary key,"
     "name varchar(255) NOT NULL)";
   tableList.append(qEventsCategories);
    QString iEventsCategories = "INSERT INTO events_categories (ID, name) VALUES"
            "(1, 'Default')";
    tableList.append(iEventsCategories);
    //genre
    QString qGenre = "CREATE TABLE IF NOT EXISTS genre ("
                "ID int(11) primary key,"
                "name varchar(50) NOT NULL)";
    tableList.append(qGenre);
    QString iGenre = "INSERT INTO genre (id, name) VALUES"
            "(1, 'Acapella'),(2, 'Acid'),"
            "(3, 'Acid Jazz'),(4, 'Acid Punk'),"
            "(5, 'Acoustic'),(6, 'Alternative'),"
            "(7, 'Alternative Rock'), (8, 'Ambient'),"
            "(9, 'Anime'),(10, 'Avantgarde'),(11, 'Ballad'),"
            "(12, 'Bass'),(13, 'Beat'),(14, 'Bebob'),"
           " (15, 'Big Band'),(16, 'Black Metal'),(17, 'Bluegrass'),"
            "(18, 'Blues'),(19, 'Booty Bass'),(20, 'BritPop'),"
           " (21, 'Cabaret'), (22, 'Celtic'),(23, 'Chamber Music'),"
            "(24, 'Chanson'), (25, 'Chorus'),(26, 'Christian Gangsta Rap'),"
            "(27, 'Christian Rap'),(28, 'Christian Rock'),(29, 'Classic Rock'),"
            "(30, 'Classical'),(31, 'Club'),(32, 'Club - House'),"
            "(33, 'Comedy'),(34, 'Contemporary Christian'),"
            "(35, 'Country'),(36, 'Crossover'),(37, 'Cult'),"
            "(38, 'Dance'),(39, 'Dance Hall'),(40, 'Darkwave'),"
            "(41, 'Death Metal'),(42, 'Disco'),(43,'Dream'),"
            "(44, 'Drum & Bass'),(45, 'Drum Solo'),(46, 'Duet'),"
            "(47, 'Easy Listening'),(48, 'Electronic'),(49, 'Ethnic'),"
            "(50, 'Euro-House'),(51, 'Euro-Techno'),(52, 'Eurodance'),(53, 'Fast Fusion'),"
            "(54, 'Folk'),(55, 'Folk-Rock'),(56, 'Folklore'),(57, 'Freestyle'),"
            "(58, 'Funk'),(59, 'Fusion'),(60, 'Game'),(61, 'Gangsta'),"
            "(62, 'Goa'), (63, 'Gospel'),(64, 'Gothic'),"
            "(65, 'Gothic Rock'),(66, 'Grunge'),(67, 'Hard Rock'),"
            "(68, 'Hardcore'),(69, 'Heavy Metal'),(70, 'Hip-Hop'),(71, 'House'),"
            "(72, 'Humour'),(73, 'Indie'),(74, 'Industrial'),(75, 'Instrumental'),"
            "(76, 'Instrumental Pop'),(77, 'Instrumental Rock'),(78, 'JPop'),"
            "(79, 'Jazz'),(80, 'Jazz+Funk'),(81, 'Jungle'),(82, 'Latin'),"
            "(83, 'Lo-Fi'),(84, 'Meditative'),(85, 'Merengue'),(86, 'Metal'),"
            "(87, 'Musical'),(88, 'National Folk'),(89, 'Native US'),(90, 'Negerpunk'),"
           " (91, 'New Age'),(92, 'New Wave'),(93, 'Noise'),(94, 'Oldies'),"
            "(95, 'Opera'),(96, 'Other'),(97, 'Polka'),(98, 'Polsk Punk'),"
            "(99, 'Pop'),(100, 'Pop-Folk'),(101, 'Pop/Funk'),(102, 'Porn Groove'),"
            "(103, 'Power Ballad'),(104, 'Pranks'),(105, 'Primus'),(106, 'Progressive Rock'),"
            "(107, 'Psychadelic'),(108, 'Psychedelic Rock'),(109, 'Punk'), (110, 'Punk Rock'),"
             "(111, 'R&B'),(112, 'Rap'),(113, 'Rave'),(114, 'Reggae'),(115, 'Retro'),"
             "(116, 'Revival'),(117, 'Rhythmic Soul'),(118, 'Rock'),(119, 'Rock & Roll'),"
            "(122, 'Satire'),(123, 'Showtunes'),(120, 'Salsa'),(121, 'Samba'),"
            "(124, 'Ska'),(125, 'Slow Jam'),(126, 'Slow Rock'),(127, 'Sonata'),"
            "(128, 'Soul'),(129, 'Sound Clip'),(130, 'Soundtrack'),(131, 'Southern Rock'),"
            "(132, 'Space'),(133, 'Speech'),(134, 'Swing'),(135, 'Symphonic Rock'),"
            "(136, 'Symphony'),(137, 'Synthpop'), (138, 'Tango'),(139, 'Techno'),"
            "(140, 'Techno-Industrial'),(141, 'Terror'),(142, 'Thrash Metal'),(143, 'Top 40'),"
            "(144, 'Trailer'),(145, 'Trance'),(146, 'Tribal'),(147, 'Trip-Hop'),(148, 'Vocal')";
    tableList.append(iGenre);
    //history
    QString qHistory = "CREATE TABLE IF NOT EXISTS `history` ("
            "`ID` int(11) primary key,"
            "`trackID` int(11) NOT NULL,"
            "`date_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`song_type` INT(2) NOT NULL,"
            "`id_subcat` int(11) NOT NULL,"
            "`id_genre` int(11) NOT NULL,"
            "`duration` double(11,5) NOT NULL,"
            "`artist` varchar(255)  NOT NULL,"
            "`original_artist` varchar(255) NOT NULL,"
            "`title` varchar(255) NOT NULL,"
            "`album` varchar(255) NOT NULL,"
            "`composer` varchar(255) NOT NULL,"
            "`label` varchar(255) NOT NULL,"
            "`year` varchar(4) NOT NULL DEFAULT '1900',"
            "`track_no` int(6) NOT NULL DEFAULT '0',"
            "`disc_no` int(6) NOT NULL DEFAULT '0',"
            "`publisher` varchar(255) NOT NULL,"
            "`copyright` varchar(255) NOT NULL,"
            "`isrc` varchar(255) NOT NULL,"
            "`listeners` int(9) DEFAULT NULL)";
    tableList.append(qHistory);
    //playlists
    QString qPlaylist = "CREATE TABLE IF NOT EXISTS `playlists` ("
            "`ID` int(11) primary key,"
            "`name` varchar(255) NOT NULL)";
    tableList.append(qPlaylist);
    //playlists_list
    QString qPlaylistList = "CREATE TABLE IF NOT EXISTS `playlists_list` ("
            "`ID` int(11) primary key,"
            "`pID` int(11) NOT NULL,"
            "`sID` int(11) NOT NULL,"
            "`cstart` DOUBLE(11, 5) NOT NULL,"
            "`cnext` DOUBLE(11, 5) NOT NULL,"
            "`cend` DOUBLE(11, 5) NOT NULL,"
            "`fin` DOUBLE(11, 5) NOT NULL,"
            "`fout` DOUBLE(11, 5) NOT NULL,"
            "`swID` int(11) NOT NULL,"
            "`swplay` DOUBLE(11, 5) NOT NULL,"
            "`vtID` int(11) NOT NULL,"
            "`vtplay` DOUBLE(11, 5) NOT NULL,"
            "`swfirst` BOOL NOT NULL DEFAULT '0',"
            "`ord` int(11) NOT NULL )";
    tableList.append(qPlaylistList);
    //queuelist
    QString qQueuelist = "CREATE TABLE IF NOT EXISTS `queuelist` ("
            "`ID` int(11) primary key,"
            "`songID` int(11) NOT NULL DEFAULT '0',"
            "`artist` varchar(250) NOT NULL,"
            "`swID` int(11) NOT NULL DEFAULT '-1',"
            "`swPlay` DOUBLE(11, 5) NOT NULL DEFAULT '0',"
            "`vtID` int(11) NOT NULL DEFAULT '-1',"
            "`vtPlay` DOUBLE(11, 5) NOT NULL DEFAULT '0') ";
    tableList.append(qQueuelist);
    //requests
    QString qRequests = "CREATE TABLE IF NOT EXISTS `requests` ("
            "`ID` int(11) primary key,"
            "`songID` int(11) NOT NULL,"
            "`username` varchar(255) NOT NULL DEFAULT 'Anomymous',"
            "`userIP` varchar(50) NOT NULL,"
            "`message` text,"
            "`requested` datetime NOT NULL,"
            "`played` int(1) NOT NULL DEFAULT '0')";
    tableList.append(qRequests);
    //roatations
    QString qRoatations = "CREATE TABLE IF NOT EXISTS `rotations` ("
            "`ID` int(11) primary key,"
            "`name` varchar(255) NOT NULL)";
    tableList.append(qRoatations);
    //rotations_list
    QString qRotationslist = "CREATE TABLE IF NOT EXISTS `rotations_list` ("
            "`ID` int(11) primary key,"
            "`pID` int(11) NOT NULL,"
            "`catID` int(11) NOT NULL,"
            "`subID` int(11) NOT NULL,"
            "`genID` int(11) NOT NULL,"
            "`mood` VARCHAR(250) NULL DEFAULT NULL,"
            "`gender` VARCHAR(250) NULL DEFAULT NULL,"
            "`language` VARCHAR(250) NULL DEFAULT NULL,"
            "`start_type` INT(11) NOT NULL DEFAULT '0',"
            "`end_type` INT(11) NOT NULL DEFAULT '0',"
            "`selType` int(1) NOT NULL,"
            "`sweeper` int(1) NOT NULL,"
            "`repeatRule` BOOL NOT NULL DEFAULT 0,"
            "`ord` int(2) NOT NULL,"
            "`data` TEXT NOT NULL,"
            "`track_separation` INT NOT NULL DEFAULT '0',"
            "`artist_separation` INT NOT NULL DEFAULT '0',"
            "`title_separation` INT NOT NULL DEFAULT '0',"
            "`album_separation` INT NOT NULL DEFAULT '0',"
            "`advanced` TEXT NULL)";
    tableList.append(qRotationslist);
    //songs
    QString qSongs = "CREATE TABLE IF NOT EXISTS `songs` ("
            "`ID` int(11) primary key,"
            "`path` varchar(255) NOT NULL,"
            "`enabled` int(1) NOT NULL DEFAULT '0',"
            "`date_added` datetime DEFAULT '2002-01-01 00:00:01',"
            "`date_modified` datetime DEFAULT '2002-01-01 00:00:01',"
            "`date_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`artist_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`album_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`title_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`count_played` int(9) NOT NULL DEFAULT '0',"
            "`play_limit` int(11) NOT NULL DEFAULT '0',"
            "`limit_action` int(1) NOT NULL DEFAULT '0',"
            "`start_date` datetime DEFAULT '2002-01-01 00:00:01',"
            "`end_date` datetime DEFAULT '2002-01-01 00:00:01',"
            "`startEvent` INT(11) NOT NULL DEFAULT '-1',"
            "`endEvent` INT(11) NOT NULL DEFAULT '-1',"
            "`song_type` INT(2) NOT NULL,"
            "`id_subcat` int(11) NOT NULL,"
            "`id_genre` int(11) NOT NULL,"
            "`weight` double(5,1) NOT NULL DEFAULT '50.0',"
            "`duration` double(11,5) NOT NULL,"
            "`original_duration` double(11,5) NOT NULL,"
            "`cue_times` varchar(255) NOT NULL DEFAULT '&',"
            "`precise_cue` INT(1) NOT NULL DEFAULT '0',"
            "`fade_type` INT(1) NOT NULL DEFAULT '0',"
            "`start_type` INT(1) NOT NULL DEFAULT '0',"
            "`end_type` INT(1) NOT NULL DEFAULT '0',"
            "`mix_type` INT(1) NOT NULL DEFAULT '0',"
            "`mood` varchar(150) NOT NULL DEFAULT 'Not Set',"
            "`gender` varchar(150) NOT NULL DEFAULT 'Not Set',"
            "`lang` varchar(150) NOT NULL DEFAULT 'Not Set',"
            "`rating` INT(1) NOT NULL DEFAULT '0',"
            "`loudness` double(11,2) NOT NULL DEFAULT '1.00',"
            "`overlay` INT(1) NOT NULL DEFAULT '0',"
            "`artist` varchar(255) NOT NULL,"
            "`original_artist` varchar(255) NOT NULL,"
            "`title` varchar(255) NOT NULL,"
            "`album` varchar(255) NOT NULL,"
            "`composer` varchar(255) NOT NULL,"
            "`label` varchar(255) NOT NULL,"
            "`year` varchar(4) NOT NULL DEFAULT '1900',"
            "`track_no` int(6) NOT NULL DEFAULT '0',"
            "`disc_no` int(6) NOT NULL DEFAULT '0',"
            "`publisher` varchar(255) NOT NULL,"
            "`copyright` varchar(255) NOT NULL,"
            "`isrc` varchar(255) NOT NULL,"
            "`bpm` double(11,1) NOT NULL,"
            "`comments` text,"
            "`sweepers` varchar(250) DEFAULT NULL,"
            "`image` varchar(255) NOT NULL DEFAULT 'no_image.jpg',"
            "`buy_link` varchar(255) NOT NULL DEFAULT 'http://',"
            "`url1` varchar(255) NOT NULL DEFAULT 'http://',"
            "`url2` varchar(255) NOT NULL DEFAULT 'http://',"
            "`tdate_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`tartist_played` datetime DEFAULT '2002-01-01 00:00:01',"
            "`originalmetadata` INT(1) NOT NULL DEFAULT '0')";
    tableList.append(qSongs);
    //subcategory
    QString qSubcategory = "CREATE TABLE IF NOT EXISTS `subcategory` ("
            "`ID` int(11) primary key,"
            "`parentid` int(11) NOT NULL,"
            "`name` varchar(100) NOT NULL)";
    tableList.append(qSubcategory);
    QString iSubcategory = "INSERT INTO `subcategory` (`ID`, `parentid`, `name`) VALUES"
            "(1, 1, '90s'),(2, 1, '80s'), (3, 1, 'Oldies'),(4, 1, '2000s'),"
            "(5, 1, 'Heavy Rotation'),(6, 1, 'Top 40'),"
            "(7, 2, 'Contest Effects'),(8, 3, 'Daily Sweepers'),"
            "(9, 3, 'Nightly Sweepers'),(10, 4, 'Artist IDs'),"
            "(11, 5, 'Station Jingles'),(12, 6, 'Radio Show Promos'),"
            "(13, 7, 'Sponsor Commercials'), (14, 7, 'Paid Commercials'),"
            "(15, 8, 'Daily News'),(16, 9, 'Music Interviews'),"
            "(17, 9, 'Political Interviews'),(18, 10, 'My First Show'),"
            "(19, 10, 'My Second Show'),(20, 11, 'Other'),"
            "(21, 11, 'Syndicated Shows'),(22, 11, 'Syndicated News')";
    tableList.append(iSubcategory);

    //users
    QString qSource = "CREATE TABLE `users` ("
            "`ID` INT(10) primary key,"
            "`user` VARCHAR(100) NOT NULL,"
            "`auth` VARCHAR(250) NULL DEFAULT NULL,"
            "`data` TEXT NOT NULL)";
    tableList.append(qSource);
    //settings
    QString qSettings = "CREATE TABLE `settings` ("
            "`source` VARCHAR(150) NOT NULL,"
            "`setting` VARCHAR(150) NOT NULL,"
            "`value` VARCHAR(250) NOT NULL)";
    tableList.append(qSettings);
    qDebug() << tableList.count();
    return tableList;
}

// remove entry from database
bool DBA::remove(QString &q)
{
    QString qs = q;
    return false;
}

// update entry in database
bool DBA::update(QString &q)
{
    QString qs = q;
    return false;
}

bool DBA::createMetaDataTable(QString q)
{
    // Run queries to create the required tables
    QSqlQuery query;
    if(query.exec(q))
    {
        qDebug() << "result of query.exec success";
        qDebug() << query.lastQuery();
        return true;
    }
    else
    {
        qDebug() << "result of query.exec failed";
        qDebug() << query.lastError();
    }
    return false;
}
