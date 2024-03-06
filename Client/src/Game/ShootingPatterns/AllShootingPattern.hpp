#ifndef _ALLSHOOTINGPATTERN_H_
#define _ALLSHOOTINGPATTERN_H_

#include "ShootingPatternAbstract.hpp"
#include "../Projectils/ProjectilAbstract.hpp"

#include <memory>

class ShootingPatternDoubleRegular final : public ShootingPatternAbstract
{
    public:

    ShootingPatternDoubleRegular() noexcept : ShootingPatternAbstract(1) {}

    std::list<std::unique_ptr<ProjectilAbstract>> getBullets(ProjectilAbstract *(*const makeProj)(const PointInSpaceDS&, Dir, float, float),
        Dir givenDir, const PointInSpaceDS& objPos, const ShapeRectangle &shapeObj) const override
        {
            std::list<std::unique_ptr<ProjectilAbstract>> projectiles;
            double startingX1, startingY1, startingX2, startingY2;

            startingX1 = objPos.x - 0.5;
            startingX2 = objPos.x + 0.5;
            if (givenDir == UP){
                startingY1 = shapeObj.getMinY(objPos.y) - 1 ;
                startingY2 = shapeObj.getMinY(objPos.y) - 1 ;
            }
            else{
                startingY1 = shapeObj.getMaxY(objPos.y) + 1;
                startingY2 = shapeObj.getMaxY(objPos.y) + 1;
            }
            projectiles.emplace_back(makeProj({startingX1, startingY1}, givenDir, 0, 1));
            projectiles.emplace_back(makeProj({startingX2, startingY2}, givenDir, 0, 1));
            return projectiles;
        };
};

class ShootingPatternLine final : public ShootingPatternAbstract
{
    public:
    ShootingPatternLine() noexcept : ShootingPatternAbstract(1) {}
    std::list<std::unique_ptr<ProjectilAbstract>> getBullets(ProjectilAbstract *(*const makeProj)(const PointInSpaceDS&, Dir, float, float),
        Dir givenDir, const PointInSpaceDS& objPos, const ShapeRectangle &shapeObj) const override
        {
            std::list<std::unique_ptr<ProjectilAbstract>> projectiles;
            double startingX, startingY;

            startingX = objPos.x;

            if (givenDir == UP) startingY = shapeObj.getMinY(objPos.y) - 1 ;
            else startingY = shapeObj.getMaxY(objPos.y) + 1;

            projectiles.emplace_back(makeProj({startingX, startingY}, givenDir, 0, 1));
            return projectiles;
        };
};

class ShootingPatternSun final : public ShootingPatternAbstract
{
    public:
    ShootingPatternSun() noexcept : ShootingPatternAbstract(1) {}
    std::list<std::unique_ptr<ProjectilAbstract>> getBullets(ProjectilAbstract *(*const makeProj)(const PointInSpaceDS&, Dir, float, float),
        Dir givenDir, const PointInSpaceDS& objPos, const ShapeRectangle &shapeObj) const override
        {
            std::list<std::unique_ptr<ProjectilAbstract>> projectiles;
            double startingX1, startingY1, startingX2, startingY2, startingX3, startingY3, startingX4, startingY4;

            //3 projectiles qui partent vers le haut de la fenêtre :
            startingX1 = objPos.x;
            startingY1 = shapeObj.getMinY(objPos.y) - 1;
            //1 projectile qui part vers la droite de la fenêtre :
            startingX2 = shapeObj.getMaxX(objPos.x) + 1;
            startingY2 = objPos.y;
            //3 projectiles qui partent vers le bas de la fenêtre :
            startingX3 = objPos.x;
            startingY3 = shapeObj.getMaxY(objPos.y) + 1;
            //1 projectile qui part vers la gauche de la fenêtre :
            startingX4 = shapeObj.getMinX(objPos.x) - 1;
            startingY4 = objPos.y;

            projectiles.emplace_back(makeProj({startingX1, startingY1}, UP, 0, 1));
            projectiles.emplace_back(makeProj({startingX1, startingY1}, UP, -1, 1));
            projectiles.emplace_back(makeProj({startingX1, startingY1}, UP, 1, 1));
            projectiles.emplace_back(makeProj({startingX2, startingY2}, UP, 1, 0));
            projectiles.emplace_back(makeProj({startingX3, startingY3}, DOWN, 1, 1));
            projectiles.emplace_back(makeProj({startingX3, startingY3}, DOWN, 0, 1));
            projectiles.emplace_back(makeProj({startingX3, startingY3}, DOWN, -1, 1));
            projectiles.emplace_back(makeProj({startingX4, startingY4}, DOWN, -1, 0));

            return projectiles;
        }
};

class ShootingPatternTripleShot final : public ShootingPatternAbstract
{
    public:
    ShootingPatternTripleShot() noexcept : ShootingPatternAbstract(1) {}
    std::list<std::unique_ptr<ProjectilAbstract>> getBullets(ProjectilAbstract *(*const makeProj)(const PointInSpaceDS&, Dir, float, float),
        Dir givenDir, const PointInSpaceDS& objPos, const ShapeRectangle &shapeObj) const override
        {
            std::list<std::unique_ptr<ProjectilAbstract>> projectiles;
            double startingX1, startingY1, startingX2, startingY2, startingX3, startingY3;

            startingX1 = startingX2 = startingX3 = objPos.x;
            if (givenDir == UP) startingY1 = startingY2 = startingY3 = shapeObj.getMinY(objPos.y) - 1 ;
            else startingY1 = startingY2 = startingY3 = shapeObj.getMaxY(objPos.y) + 1;

            projectiles.emplace_back(makeProj({startingX3, startingY3}, givenDir, -1, 1));
            projectiles.emplace_back(makeProj({startingX3, startingY3}, givenDir, 0, 1));
            projectiles.emplace_back(makeProj({startingX3, startingY3}, givenDir, 1, 1));

            return projectiles;
        };
};

#endif