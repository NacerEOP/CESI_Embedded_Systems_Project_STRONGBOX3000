# CESI_Embedded_Systems_Project_STRONGBOX3000
Nous sommes positionnés en tant qu'une équipe de conception en ingénierie qui a été désignée pour travailler sur un projet qui pourrait régler une bonne fois pour toutes le problème que l'MI7 a rencontré : un coffre-fort qui requiert plusieurs touches de sécurité pour s'ouvrir.

<img width="1280" height="606" alt="image" src="https://github.com/user-attachments/assets/43ac0b40-699f-4acf-ba35-98d109fdeb1f" />

Ce projet, intitulé StrongBox 3000, avait pour objectif de nous placer dans une situation réelle de conception en ingénierie. À partir d’un besoin de sécurité exprimé sous forme de scénario, nous devions imaginer, modéliser et réaliser un prototype de coffre-fort nouvelle génération intégrant plusieurs mécanismes d’authentification. Le travail demandait l’application d’une démarche complète allant de l’analyse fonctionnelle à la réalisation d’un Proof of Concept validé par une maquette physique basée sur Arduino.

<img width="1280" height="606" alt="image" src="https://github.com/user-attachments/assets/18a2cb68-0976-418f-aae4-8529c062fe65" />

Le projet imposait la conception d’un système d’authentification hiérarchisé. Une première étape consistait à identifier des cartes électroniques à l’aide de combinaisons d’interrupteurs et de circuits logiques, puis à reconnaître automatiquement le modèle de carte inséré dans le coffre. Cette reconnaissance devait être réalisée à l’aide d’un montage électronique utilisant des résistances normalisées, des transistors et des LEDs, produisant des tensions spécifiques mesurées par l’Arduino. En parallèle, il était demandé de modéliser les circuits logiques associés à chaque carte et au coffre, de produire les tables de vérité, les schémas Logisim et les simplifications nécessaires pour une implémentation physique optimisée.

<img width="1280" height="606" alt="image" src="https://github.com/user-attachments/assets/0f1d9a29-816f-4cd7-96ad-acf5e8727b4a" />


Une fois l’identification de la carte validée, le système devait déterminer un niveau de sécurité et déclencher une combinaison de mécanismes d’authentification : code temporel, questions-réponses, authentifications simulées (scan digital et rétinien) et, de manière optionnelle, un mécanisme de chiffrement RSA. L’ensemble du comportement du coffre devait être décrit à l’aide de logigrammes précis, puis implémenté sous forme d’un programme Arduino structuré, modulaire et documenté.

<img width="1280" height="606" alt="image" src="https://github.com/user-attachments/assets/8d9af299-229b-44ee-86dc-e6dd89fbe3a8" />

Les principaux acquis d’apprentissage concernent la maîtrise de la démarche de conception en ingénierie, la modélisation de systèmes logiques complexes, la traduction de portes logiques en circuits électroniques réels à l’aide de composants discrets, ainsi que le dimensionnement de résistances et l’exploitation de mesures analogiques sur microcontrôleur. Le projet a également permis de développer des compétences en algorithmique, en structuration de programme embarqué, en gestion de données (tableaux, variables, portée) et en communication entre matériel et logiciel. Enfin, ce travail a renforcé les capacités de travail en équipe, de documentation technique et de justification des choix techniques dans un contexte de contraintes réelles.
