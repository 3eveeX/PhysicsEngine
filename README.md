# 2D Physics Engine

A real-time 2D physics simulation environment featuring interactive object placement, configurable physics bodies, force effectors, spring constraints, and extensive world customisation through an integrated graphical user interface.

---

## Overview

This project is a 2D physics engine designed for experimentation, simulation, and educational purposes. Users can build dynamic scenes by placing physics bodies and effectors directly into the world, connecting objects with springs, and adjusting simulation parameters in real time.

The engine provides intuitive mouse-driven controls alongside a comprehensive GUI for configuring individual objects and global simulation behaviour.

---

## Features

### Physics Bodies

Create and simulate three different body types:

| Body Type     | Description                                                                                                   |
| ------------- | ------------------------------------------------------------------------------------------------------------- |
| **Dynamic**   | Fully simulated bodies affected by forces, gravity, collisions, and springs.                                  |
| **Kinematic** | User-controlled bodies that move independently of physical forces while still interacting with other objects. |
| **Static**    | Immovable objects used for floors, walls, and obstacles.                                                      |

Each body can be individually configured through the GUI with properties including:

* Mass
* Size
* Bounciness (restitution)
* Gravity influence
* Body type
* Additional simulation parameters

---

### Effectors

The engine supports four force-generating effectors that influence nearby bodies:

| Effector Type              | Description                                          |
| -------------------------- | ---------------------------------------------------- |
| **Point Effector**         | Applies force toward or away from a central point.   |
| **Gravitational Effector** | Simulates localised gravitational attraction.        |
| **Area Effector**          | Applies directional force within a specified region. |
| **Drag Effector**          | Simulates resistance and damping effects.            |

Each effector can be configured through the GUI, including:

* Force strength
* Force direction
* Area of influence
* Additional effector-specific properties

---

### Spring System

Bodies can be connected using spring constraints to create ropes, chains, suspension systems, and other physically linked structures.

Configurable spring properties include:

* Stiffness
* Rest length
* Global spring stiffness multiplier

---

### World Configuration

The simulation environment itself can be customised in real time through the GUI.

Available settings include:

* Global gravity
* World spring stiffness
* Target FPS
* Additional simulation-wide parameters

---

## Controls

### Body Placement

| Action            | Result                             |
| ----------------- | ---------------------------------- |
| Left Click        | Place a single body                |
| Ctrl + Left Click | Continuously place multiple bodies |

---

### Effector Placement

| Action            | Result                                |
| ----------------- | ------------------------------------- |
| Left Click        | Place a single effector               |
| Ctrl + Left Click | Continuously place multiple effectors |

---

### Spring Creation

1. Right-click on the first body.
2. Hold the mouse button.
3. Drag to the second body.
4. Release over the target body.

A spring will be created between the selected bodies using the currently configured spring settings.

---

## Graphical User Interface

The integrated GUI provides complete control over both object-level and world-level settings.

### Body Settings

* Body type selection
* Mass
* Size
* Bounciness
* Gravity scale
* Additional body properties

### Effector Settings

* Effector type
* Force strength
* Force direction
* Influence parameters

### Spring Settings

* Spring stiffness
* Spring length
* Global spring behaviour

### World Settings

* Global gravity
* Simulation FPS
* Global spring stiffness
* Engine-wide parameters

Changes made through the GUI are reflected immediately within the simulation, allowing for rapid iteration and testing.

---

## Use Cases

This engine is suitable for:

* Physics experimentation
* Educational demonstrations
* Gameplay prototyping
* Constraint and spring simulations
* Force field visualisation
* Sandbox environments
* Academic projects

---

## Example Scenarios

* Build a bridge using spring-connected bodies.
* Create a pendulum system with adjustable stiffness.
* Simulate orbital attraction using gravitational effectors.
* Construct particle systems affected by area forces.
* Test collision behaviour using different body types and restitution values.

---

## Technical Highlights

* Real-time rigid body simulation
* Interactive object creation
* Multiple force effector types
* Configurable spring constraints
* Dynamic parameter editing
* Adjustable simulation timestep/FPS
* Modular world settings

---

## Future Improvements

Potential future additions include:

* Save and load functionality
* Collision layers and filtering
* Rotational constraints
* Distance and hinge joints
* Scene presets
* Performance profiling tools
* Advanced debugging visualisations

---

## License

This project is provided for educational and development purposes. Modify and extend the engine as needed for your own simulations and applications.
