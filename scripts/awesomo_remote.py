#!/usr/bin/env python
from math import pi
from time import sleep

import rospy

from awesomo import Camera
from awesomo import LandingZone
from awesomo import Gimbal
from awesomo import Quadrotor
from awesomo import MAVROS


def lz_circle_path(radius, velocity):
    # calculate time taken to complete circle
    distance = 2 * pi * radius
    time_taken = distance / velocity

    # angular velocity needed to make circle path
    angular_velocity = (2 * pi) / time_taken

    return (velocity, angular_velocity)


def lz_circle(radius, velocity):
    velocity, angular_velocity = lz_circle_path(radius, velocity)
    lz.set_velocity(velocity)
    lz.set_angular_velocity(angular_velocity)


def lz_straight_line(velocity):
    lz.set_velocity(velocity)
    lz.set_position([0, 0, 0])


def side_to_side(quad, altitude, dist):
    for i in range(10):
        side_1 = [dist, 0.0, altitude]
        quad.set_hover_point(side_1)
        print(side_1)
        sleep(5)

        side_2 = [-dist, 0.0, altitude]
        quad.set_hover_point(side_2)
        print(side_2)
        sleep(5)


def square(quad, altitude, width):
    for i in range(10):
        wp1 = [width, width, altitude]
        quad.set_hover_point(wp1)
        print(wp1)
        sleep(5)

        wp2 = [-width, width, altitude]
        quad.set_hover_point(wp2)
        print(wp2)
        sleep(5)

        wp3 = [-width, -width, altitude]
        quad.set_hover_point(wp3)
        print(wp3)
        sleep(5)

        wp4 = [width, -width, altitude]
        quad.set_hover_point(wp4)
        print(wp4)
        sleep(5)


def init_svo(lz):
    for i in range(2):
        lz.set_position([0, 0, 0])
        sleep(1)

        lz.set_position([0, -0.4, 0])
        sleep(1)

        lz.set_position([-0.4, 0, 0])
        sleep(1)

        lz.set_position([0, 0.4, 0])
        sleep(1)

        lz.set_position([0.4, 0, 0])
        sleep(1)


if __name__ == "__main__":
    rospy.init_node("awesomo_remote")
    lz = LandingZone()
    camera = Camera()
    quad = Quadrotor()
    gimbal = Gimbal()
    mavros = MAVROS()
    rospy.sleep(1.0)

    quad.set_arm(True)
    # quad.set_hover_point([0.0, 0.0, 10.0])

    # quad.set_hover_point([0.0, 0.0, 5.0])

    sleep(2)
    # quad.set_mode("HOVER")
    # quad.set_hover_point([0.0, 0.0, 5.0])
    # quad.set_yaw(-20)

    # square(quad, 3, 1)
    # lz_circle(20, 1.0)
    lz_straight_line(1.0)
    # lz.set_position([0, 0, 0])

    # side_to_side(quad, 4.0, 2.0)
    # square(quad, 4.0, 2.0)

    # quad.set_pctrl_settings({
    #     "roll": {
    #         "min": -30,
    #         "max": 30,
    #         "k_p": 0.3,
    #         "k_i": 0.0,
    #         "k_d": 0.2
    #     },
    #     "pitch": {
    #         "min": -30,
    #         "max": 30,
    #         "k_p": 0.3,
    #         "k_i": 0.0,
    #         "k_d": 0.2
    #     },
    #     "throttle": {
    #         "hover": 0.5,
    #         "k_p": 0.4,
    #         "k_i": 0.0,
    #         "k_d": 0.2
    #     }
    # })

    # quad.set_tctrl_settings({
    #     "roll": {
    #         "min": -30,
    #         "max": 30,
    #         "k_p": 0.8,
    #         "k_i": 0.00001,
    #         "k_d": 0.2
    #     },
    #     "pitch": {
    #         "min": -30,
    #         "max": 30,
    #         "k_p": 0.1,
    #         "k_i": 0.0,
    #         "k_d": 0.05
    #     },
    #     "throttle": {
    #         "hover": 0.5,
    #         "k_p": 0.4,
    #         "k_i": 0.0,
    #         "k_d": 0.2
    #     },
    #     "vx": {
    #         "k_p": 0.2,
    #         "k_i": 0.0,
    #         "k_d": 0.0
    #     },
    #     "vy": {
    #         "k_p": 0.5,
    #         "k_i": 0.0,
    #         "k_d": 0.0
    #     },
    #     "vz": {
    #         "k_p": 0.2,
    #         "k_i": 0.0,
    #         "k_d": 0.0
    #     }
    # })
