#pragma once

#include "Tree.h"

#include <thread>
#include <SFML/Graphics.hpp>
#include <initializer_list>
#include <vector>
#include <format>

template <class T>
class GraphicsTree {
    struct TreeSettings {
        TreeNode<T> *p;
        float radius;
        std::size_t left_x, right_x, y;
    };

    static void __initLeafs__(std::vector<sf::CircleShape> &leafs, const TreeSettings &sett) {
        if (sett.p != nullptr) {
            sf::CircleShape leaf(sett.radius);
            leaf.setPosition(sf::Vector2f((sett.left_x + sett.right_x) / 2 - sett.radius, sett.y));
            leaf.setFillColor(sf::Color::Green);
            leafs.push_back(leaf);

            TreeSettings new_sett = sett;

            new_sett.p = sett.p->left;
            new_sett.right_x = (sett.left_x + sett.right_x) / 2;
            new_sett.y = sett.y + 20 + static_cast<std::size_t>(sett.radius) * 2;
            __initLeafs__(leafs, new_sett);

            new_sett.p = sett.p->right;
            new_sett.left_x = (sett.left_x + sett.right_x) / 2;
            new_sett.right_x = sett.right_x;
            __initLeafs__(leafs, new_sett);
        }
    }

    static void __initBranches__(std::vector<sf::ConvexShape> &branches, const TreeSettings &sett) {
        if (sett.p != nullptr) {
            sf::ConvexShape branch(4);
            branch.setFillColor(sf::Color(94, 0, 0));
            branch.setPoint(0, sf::Vector2f((sett.left_x + sett.right_x) / 2, sett.y + static_cast<std::size_t>(sett.radius)));
            branch.setPoint(1, sf::Vector2f(branch.getPoint(0).x, branch.getPoint(0).y + 2));

            if (sett.p->left != nullptr) {
                branch.setPoint(2, sf::Vector2f((3 * sett.left_x + sett.right_x) / 4 + 2, sett.y + 22 + static_cast<std::size_t>(sett.radius) * 3));
                branch.setPoint(3, sf::Vector2f((3 * sett.left_x + sett.right_x) / 4, sett.y + 20 + static_cast<std::size_t>(sett.radius) * 3));
                branches.push_back(branch);

                TreeSettings new_sett = sett;

                new_sett.p = sett.p->left;
                new_sett.right_x = (sett.left_x + sett.right_x) / 2;
                new_sett.y = sett.y + 20 + static_cast<std::size_t>(sett.radius) * 2;
                __initBranches__(branches, new_sett);
            }
            if (sett.p->right != nullptr) {
                branch.setPoint(2, sf::Vector2f((sett.left_x + 3 * sett.right_x) / 4 - 2, sett.y + 22 + static_cast<std::size_t>(sett.radius) * 3));
                branch.setPoint(3, sf::Vector2f((sett.left_x + 3 * sett.right_x) / 4, sett.y + 20 + static_cast<std::size_t>(sett.radius) * 3));
                branches.push_back(branch);

                TreeSettings new_sett = sett;

                new_sett.p = sett.p->right;
                new_sett.left_x = (sett.left_x + sett.right_x) / 2;
                new_sett.y = sett.y + 20 + static_cast<std::size_t>(sett.radius) * 2;
                __initBranches__(branches, new_sett);
            }
        }
    }

    static void __initText__(std::vector<sf::Text> &numbers, const sf::Font &font, const TreeSettings &sett, const std::locale &loc) {
        if (sett.p != nullptr) {
            sf::Text number;
            number.setString(sf::String(std::format("{}", sett.p->value), loc));
            number.setFont(font);
            number.setCharacterSize(static_cast<unsigned>(sett.radius));
            number.setFillColor(sf::Color::Black);
            number.setPosition(sf::Vector2f((sett.left_x + sett.right_x - sett.radius) / 2.f, static_cast<float>(sett.y)));
            numbers.push_back(number);

            TreeSettings new_sett = sett;

            new_sett.p = sett.p->left;
            new_sett.right_x = (sett.left_x + sett.right_x) / 2;
            new_sett.y = sett.y + 20 + static_cast<std::size_t>(sett.radius) * 2;
            __initText__(numbers, font, new_sett, loc);

            new_sett.p = sett.p->right;
            new_sett.left_x = (sett.left_x + sett.right_x) / 2;
            new_sett.right_x = sett.right_x;
            __initText__(numbers, font, new_sett, loc);
        }
    }

    static void __veiwTree__(ITree<T> *tree, const std::locale &loc) {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        sf::RenderWindow window(sf::VideoMode(1900, 600), "Tree", sf::Style::Default, settings);

        std::vector<sf::CircleShape> leafs;
        std::vector<sf::ConvexShape> branches;
        std::vector<sf::Text> numbers;

        float radius = (static_cast<float>(window.getSize().y) / static_cast<float>(tree->getHeight()) - 20.f) / 3.f;
        sf::Font font;
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

        sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
        sf::Texture background_texture;
        background_texture.loadFromFile("tree.jpg");
        background.setTexture(&background_texture);

        TreeSettings sett = { tree->root, radius, 0, window.getSize().x, 10 };
        __initLeafs__(leafs, sett);
        __initBranches__(branches, sett);
        __initText__(numbers, font, sett, loc);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();

            window.clear(sf::Color::White);

            window.draw(background);

            for (sf::ConvexShape &branch : branches)
                window.draw(branch);
            for (sf::CircleShape &leaf : leafs)
                window.draw(leaf);
            for (sf::Text &number : numbers)
                window.draw(number);

            window.display();
        }
    }

public:
    static void veiwTree(const std::initializer_list<ITree<T> *> &init_list, const std::locale &loc = std::locale()) {
        std::vector<std::thread> threads;
        for (ITree<T> *elem : init_list)
            threads.push_back(std::thread(__veiwTree__, elem, loc));
        for (std::thread &th : threads)
            th.join();
    }
};
