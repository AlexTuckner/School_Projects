/* STUDENTS: Write your own unit tests in this file.  Or, better yet,
   rename this file to something more meaningful and/or add additional
   files of tests to this directory to test your project code in
   whatever ways you see fit!
 */

// The Google Test framework
#include <gtest/gtest.h>


// Includes for project code in the ../src directory
 #include "../src/sensor_distress.h"
 #include "../src/sensor_entity_type.h"
 #include "../src/sensor_proximity.h"
 #include "../src/sensor_touch.h"
 #include "../src/event_distress_call.h"
// #include "../src/event_proximity.h"
 #include "../src/event_collision.h"
// #include "../src/event_type_emit.h"
 #include "../src/entity_type.h"
 #include "../src/position.h"



#ifdef PRIORITY1_TESTS



// ******************************************************************
// Sensor Distress
// ******************************************************************

TEST(SensorDistress, Initialization) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  EXPECT_EQ(sd.get_entity_type(), csci3081::kPlayer);
  EXPECT_EQ(sd.get_is_activated(), 0);
  EXPECT_EQ(sd.get_range(), 10.0);

}

TEST(SensorDistress, AcceptEventCollision) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  csci3081::EventCollision ec = csci3081::EventCollision(csci3081::kWall, Position(0,0), 5.0);
  sd.Accept(&ec);
  EXPECT_EQ(sd.get_is_activated(), 0);
}

TEST(SensorDistress, AcceptEventDistress) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  csci3081::EventDistressCall ed = csci3081::EventDistressCall(csci3081::kWall, Position(0,0));
  sd.Accept(&ed);
  EXPECT_EQ(sd.get_is_activated(), 1);
}

TEST(SensorDistress, AcceptEventTypeEmit) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  sd.Accept(&ete);
  EXPECT_EQ(sd.get_is_activated(), 0);
}

TEST(SensorDistress, AcceptEventProximity) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  csci3081::EventProximity ep = csci3081::EventProximity(csci3081::kWall, Position(0,0));
  sd.Accept(&ep);
  EXPECT_EQ(sd.get_is_activated(), 0);
}

TEST(SensorDistress, Output) {
  csci3081::SensorDistress sd = csci3081::SensorDistress(csci3081::kPlayer, 0, 10.0);
  csci3081::EventDistressCall ed = csci3081::EventDistressCall(csci3081::kWall, Position(0,0));
  sd.Accept(&ed);
  EXPECT_EQ(sd.get_is_activated(), 1);
}



// ******************************************************************
// Sensor Entity Type
// ******************************************************************

TEST(SensorEntityType, Initialization){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  EXPECT_EQ(set.get_entity_type(), csci3081::kPlayer);
  EXPECT_EQ(set.get_is_activated(), 0);
  EXPECT_EQ(set.get_range(), 3.0);
}

TEST(SensorEntityType, AcceptEventCollision){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  csci3081::EventCollision ec = csci3081::EventCollision(csci3081::kWall, Position(0,0), 5.0);
  set.Accept(&ec);
  EXPECT_EQ(set.get_is_activated(),0);
}

TEST(SensorEntityType, AcceptEventDistress){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  csci3081::EventDistressCall ed = csci3081::EventDistressCall(csci3081::kWall, Position(0,0));
  set.Accept(&ed);
  EXPECT_EQ(set.get_is_activated(),0);
}

TEST(SensorEntityType, AcceptEventTypeEmit){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  set.Accept(&ete);
  EXPECT_EQ(set.get_is_activated(),1);
}

TEST(SensorEntityType, AcceptEventTypeEmitOutside){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 0.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  set.Accept(&ete);
  EXPECT_EQ(set.get_is_activated(),1);
}


TEST(SensorEntityType, AcceptEventProximity){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  csci3081::EventProximity ep = csci3081::EventProximity(csci3081::kWall, Position(0,0));
  set.Accept(&ep);
  EXPECT_EQ(set.get_is_activated(),0);
}

TEST(SensorEntityType, Output){
  csci3081::SensorEntityType set = csci3081::SensorEntityType(csci3081::kPlayer, 0, 3.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  set.Accept(&ete);
  EXPECT_EQ(set.get_is_activated(), 1);
}



// ******************************************************************
// Sensor Proximity
// ******************************************************************

TEST(SensorProximity, Initialization) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  EXPECT_EQ(sp.get_entity_type(), csci3081::kPlayer);
  EXPECT_EQ(sp.get_is_activated(), 0);
  EXPECT_EQ(sp.get_range(), 5.0);
  EXPECT_EQ(sp.get_field_of_view(), 10.0);
}

TEST(SensorProximity, AcceptEventCollision) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  csci3081::EventCollision ec = csci3081::EventCollision(csci3081::kWall, Position(0,0), 5.0);
  sp.Accept(&ec);
  EXPECT_EQ(sp.get_is_activated(), 0);
}

TEST(SensorProximity, AcceptEventDistress) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  csci3081::EventDistressCall ed = csci3081::EventDistressCall(csci3081::kWall, Position(0,0));
  sp.Accept(&ed);
  EXPECT_EQ(sp.get_is_activated(), 0);
}

TEST(SensorProximity, AcceptEventTypeEmit) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  sp.Accept(&ete);
  EXPECT_EQ(sp.get_is_activated(), 0);
}

TEST(SensorProximity, AcceptEventProximity) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  csci3081::EventProximity ep = csci3081::EventProximity(csci3081::kWall, Position(0,0));
  sp.Accept(&ep);
  EXPECT_EQ(sp.get_is_activated(), 1);
}

TEST(SensorProximity, Output) {
  csci3081::SensorProximity sp = csci3081::SensorProximity(csci3081::kPlayer, 0, 5.0, 10.0);
  csci3081::EventProximity ec = csci3081::EventProximity(csci3081::kWall, Position(0,0));
  sp.Accept(&ec);
  EXPECT_EQ(sp.get_is_activated(), 1);
}


// ******************************************************************
// Sensor Touch
// ******************************************************************
TEST(SensorTouch, Initialization) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  EXPECT_EQ(st.get_entity_type(), csci3081::kPlayer);
  EXPECT_EQ(st.get_is_activated(), 0);
  EXPECT_EQ(st.get_point_of_contact().get_x(), 0);
  EXPECT_EQ(st.get_angle_of_contact(), 90.0);
}

TEST(SensorTouch, AcceptEventCollision) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  csci3081::EventCollision ec = csci3081::EventCollision(csci3081::kWall, Position(0,0), 5.0);
  st.Accept(&ec);
  EXPECT_EQ(st.get_is_activated(), 1);
}


TEST(SensorTouch, AcceptEventDistress) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  csci3081::EventDistressCall ed = csci3081::EventDistressCall(csci3081::kWall, Position(0,0));
  st.Accept(&ed);
  EXPECT_EQ(st.get_is_activated(), 0);
}

TEST(SensorTouch, AcceptEventTypeEmit) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  csci3081::EventTypeEmit ete = csci3081::EventTypeEmit(csci3081::kWall, Position(0,0));
  st.Accept(&ete);
  EXPECT_EQ(st.get_is_activated(), 0);
}

TEST(SensorTouch, AcceptEventProximity) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  csci3081::EventProximity ep = csci3081::EventProximity(csci3081::kWall, Position(0,0));
  st.Accept(&ep);
  EXPECT_EQ(st.get_is_activated(), 0);
}

TEST(SensorTouch, Output) {
  csci3081::SensorTouch st = csci3081::SensorTouch(csci3081::kPlayer, 0, Position(0,0), 90.0);
  csci3081::EventCollision ec = csci3081::EventCollision(csci3081::kWall, Position(0,0), 5.0);
  st.Accept(&ec);
  EXPECT_EQ(st.get_is_activated(), 1);
}


#endif /* Student Iteration 2 tests */
