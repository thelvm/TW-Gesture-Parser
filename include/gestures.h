#ifndef GESTURES_H_INCLUDED
#define GESTURES_H_INCLUDED

#include <vector>

constexpr unsigned int  bits_per_hand_present = 1,
                        bits_per_finger       = 1,
                        bits_per_axis         = 3;

/// Hand position information as a bitfield
struct hand_bitfield
{
    bool operator==(const hand_bitfield &rhs) const;

    bool operator!=(const hand_bitfield &rhs) const;

    unsigned int l_hand_present : bits_per_hand_present;
    unsigned int l_thumb        : bits_per_finger;
    unsigned int l_index        : bits_per_finger;
    unsigned int l_middle       : bits_per_finger;
    unsigned int l_ring         : bits_per_finger;
    unsigned int l_pinky        : bits_per_finger;
    unsigned int l_roll         : bits_per_axis;
    unsigned int l_pitch        : bits_per_axis;
    unsigned int l_yaw          : bits_per_axis;

    unsigned int r_hand_present : bits_per_hand_present;
    unsigned int r_thumb        : bits_per_finger;
    unsigned int r_index        : bits_per_finger;
    unsigned int r_middle       : bits_per_finger;
    unsigned int r_ring         : bits_per_finger;
    unsigned int r_pinky        : bits_per_finger;
    unsigned int r_roll         : bits_per_axis;
    unsigned int r_pitch        : bits_per_axis;
    unsigned int r_yaw          : bits_per_axis;
};

/// Interface with the hand bitfield for ease of use
class hand_discrete
{
private:
    hand_bitfield handBits{};
    static unsigned int discretize_angle(double angle);

public:
    hand_discrete();
    // Is left hand present
    unsigned int get_l_hand_present() const;
    void set_l_hand_present(unsigned int x);
    // Left hand thumb. 0 is closed, 1 is extended
    unsigned int get_l_thumb() const;
    void set_l_thumb(unsigned int x);
    // Left hand index finger. 0 is closed, 1 is extended
    unsigned int get_l_index() const;
    void set_l_index(unsigned int x);
    // Left hand middle finger. 0 is closed, 1 is extended
    unsigned int get_l_middle() const;
    void set_l_middle(unsigned int x);
    // Left hand ring finge. 0 is closed, 1 is extended
    unsigned int get_l_ring() const;
    void set_l_ring(unsigned int x);
    // Left hand pinky finger. 0 is closed, 1 is extended
    unsigned int get_l_pinky() const;
    void set_l_pinky(unsigned int x);

    // Left hand roll.
    // 0 is flat palm down. Goes counter clockwise in 45� increments.
    unsigned int get_l_roll() const;
    void set_l_roll(double roll);
    // Left hand pitch.
    // 0 is flat palm down. Goes fingers up in 45� increments.
    unsigned int get_l_pitch() const;
    void set_l_pitch(double pitch);
    // Left hand yaw.
    // 0 is fingers pointing forward. Goes clockwise in 45� increments.
    unsigned int get_l_yaw() const;
    void set_l_yaw(double yaw);

    bool get_l_open() const;
    void set_l_open();
    void set_l_closed();

    // Is the right hand present
    unsigned int get_r_hand_present() const;
    void set_r_hand_present(unsigned int x);
    // Right hand thumb. 0 is closed, 1 is extended
    unsigned int get_r_thumb() const;
    void set_r_thumb(unsigned int x);
    // Right hand index finger. 0 is closed, 1 is extended
    unsigned int get_r_index() const;
    void set_r_index(unsigned int x);
    // Right hand middle finger. 0 is closed, 1 is extended
    unsigned int get_r_middle() const;
    void set_r_middle(unsigned int x);
    // Right hand ring finger. 0 is closed, 1 is extended
    unsigned int get_r_ring() const;
    void set_r_ring(unsigned int x);
    // Right hand pinky finger. 0 is closed, 1 is extended
    unsigned int get_r_pinky() const;
    void set_r_pinky(unsigned int x);

    // Right hand roll.
    // 0 is flat palm down. Goes clockwise in 45� increments.
    unsigned int get_r_roll() const;
    void set_r_roll(double roll);
    // Left hand pitch.
    // 0 is flat palm down. Goes fingers up in 45� increments.
    unsigned int get_r_pitch() const;
    void set_r_pitch(double pitch);
    // Left hand yaw.
    // 0 is fingers pointing forward. Goes clockwise in 45� increments.
    unsigned int get_r_yaw() const;
    void set_r_yaw(double yaw);

    bool get_r_open() const;
    void set_r_open();
    void set_r_closed();

    bool operator==(const hand_discrete &rhs) const;

    bool operator!=(const hand_discrete &rhs) const;

};

/// Class allowing to define custom gestures.
/// Gestures have 1 or more keyframes. Keyframes currently have no time information. They are tested as soon as the
/// previous on has been succesfully detected
class gesture
{
private:
    unsigned int nbr_tests;
    unsigned int current_keyframe;
    std::vector<hand_discrete> keyframes;
public:
    /// The name of the gesture. Also doubles as UUID
    const char* name;

    ///After how many failed tested frames should the gesture reset it's current keyframe
    unsigned int timeout;


    explicit gesture(const char *name, unsigned int timeout);

    /// Adds a keyframe to the list of keyframes
    /// Keyframes are tested in the order they are added
    void add_keyframe(hand_discrete handDiscrete);

    /// Returns true if the gesture is completed. False otherwise
    bool test(hand_discrete *handDiscrete);
};

#endif // GESTURES_H_INCLUDED
