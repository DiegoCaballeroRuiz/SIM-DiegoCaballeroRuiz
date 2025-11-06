# Memoria práctica intermedia

## Sobre la práctica

- La práctica es un juego de frontón en el que se tendrá que mantener en movimiento una bola en una pista, luchando contra *eventos aleatorios de clima* en forma de lluvia y viento en múltiples direcciones,
- El código se encuentra en un proyecto de visual studio y todo lo relevante a la entrega a nivel de ejecución es accesible en una escena, cuyo fichero de encabezado es GameScene.h

- **Features:**
    - *Mueve la vista de la cámara* arrastrando el click
    - *Mueve la cámara* con WASD
    - *Activa la lluvia* con 'l' (de lluvia)
    - *Activa el viento* con 'v' (de viento)
    - *Activa los confetti* de victoria con 'c' (de confetti)
    - *Haz un "saque"* (Lanza una bola negra en la dirección en la que mira la cámara) con 'f' (de frontón)

## Requisitos de entrega

- *A1:* método de euler semi-implícito, en el método 'integrate' de Particle.cpp.
- *A2:* parámetro 'mass' en Particle.hpp. La masa de las partículas es un parámetro de los generadores de partículas de GameScene.cpp, las partículas de viento, lluvia, confetti y bola tienen masas distintas.
- *A3:* parámetros 'mass' y 'forceSum' y métodos 'addForce' y 'integrate' en Particle.hpp.

- *B:* archivo Proyectile.h 

*-* *C:* archivo ParticleSystem.h

*-* *D1:* en lugar de crear una partícula modelo, cosa que generaba una partícula que no podía borrar en la posición del sistema, reciben como argumento todos los parámetros necesarios para crear una partícula y luego crean una nueva. Está todo en el método 'genParticle'() de las clases GaussianGenerator, UnformGenerator y PointProyectileGenerator
- *D2:* método 'genParticle' en GaussianGenerator.h y UniformGenerator.h
- *D3:* vector 'particleGenerators' y métodos 'registerParticleGenerator' y 'deRegisterParticleGenerator' en ParticleSystem.h 

*-* *E1:* método update() en ParticleSystem.cpp, hay un comentario que indica dónde se aplican las fuerzas. Se hace para cada generador y para cada partícula
- *E2:* en el método del apartado anterior, cada partícula recibe la fuerza de cada generador de fuerza
- *E3:* vector 'forceGenerators' y método 'registerForceGenerator' en ParticleSystem. En el código fuente de la escena GameScene, en el método 'toggleWind()' hay un ejemplo de cómo la fuerza del viento empieza a afectar a múltiples sistemas.
- *E4:* Por ejemplo, ExplosionForceGenerator.h para posición y TimeExplosionForceGenerator para fuerza. El primero de estos se usa para los confetti de la GameScene

## Notas adicionales

- El generador de fuerza de explosión en función del tiempo no funciona correctamente
- Se puede lanzar la bola como proyectil en vez de como partícula en la gameScene descomentando la línea 117 y comentando la línea 116, pero esto lanza la bola a una dirección distinta de la que mira la cámara y es difícil de apreciar
