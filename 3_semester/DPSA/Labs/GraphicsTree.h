#pragma once

#include "BTree.h"

#include <thread>
#include <SFML/Graphics.hpp>
#include <initializer_list>
#include <format>

template <class T, class TreeClass> class IGraphicsTree {
public:
    virtual void veiwTree(std::initializer_list<TreeClass *> init_list, const std::locale &loc = std::locale()) = 0;
};

template <class T, class TNode> class GraphicsTree : public IGraphicsTree<T, BaseTree<T, TNode>> {
    using ShareType = sf::CircleShape;
    using TreeClassType = BaseTree<T, TNode>;

    struct TreeSettings {
        TNode *p;
        float radius;
        std::size_t left_x, right_x, y;
    };

    static void __initLeafs__(std::vector<ShareType> &leafs, const TreeSettings &sett) {
        if (sett.p != nullptr) {
            ShareType leaf(sett.radius);
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

    static void __veiwTree__(TreeClassType *tree, const std::locale &loc) {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        sf::RenderWindow window(sf::VideoMode(1900, 600), "Tree", sf::Style::Default, settings);

        std::vector<ShareType> leafs;
        std::vector<sf::ConvexShape> branches;
        std::vector<sf::Text> numbers;

        float radius = (static_cast<float>(window.getSize().y) / static_cast<float>(tree->getHeight()) - 20.f) / 3.f;
        sf::Font font;
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

        sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
        sf::Texture background_texture;
        // background_texture.loadFromFile("tree.jpg");
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
            for (ShareType &leaf : leafs)
                window.draw(leaf);
            for (sf::Text &number : numbers)
                window.draw(number);

            window.display();
        }
    }

public:
    static void veiwTree(std::initializer_list<TreeClassType *> init_list, const std::locale &loc = std::locale()) {
        std::vector<std::thread> threads;
        for (TreeClassType *elem : init_list)
            threads.push_back(std::thread(__veiwTree__, elem, loc));
        for (std::thread &th : threads)
            th.join();
    }
};

template <class T, std::size_t M> class GraphicsBTree : public IGraphicsTree<T, BTree<T, M>> {
    using ShareType = sf::RectangleShape;
    using TreeClassType = BTree<T, M>;

    static const std::size_t LEVEL_STEP = 30;

    struct BTreeSettings {
        TreeClassType::Node *p;
        std::size_t width, height, x, y;
        std::size_t left_x, right_x;
    };

    static void __initLeafs__(std::vector<ShareType> &leafs, const BTreeSettings &sett) {
        if (sett.p != nullptr) {
            ShareType leaf(sf::Vector2f(sett.width, sett.height));
            leaf.setPosition(sf::Vector2f(sett.x, sett.y));
            leaf.setFillColor(sf::Color::Green);
            leafs.push_back(leaf);

            BTreeSettings new_sett;
            for (std::size_t i = 0; i < sett.p->child_nodes.size(); i++) {
                auto p = sett.p->child_nodes.at(i);
                if (p != nullptr) {
                    new_sett.p = p;
                    new_sett.width = sett.height * p->values.size() * 1.2;
                    new_sett.height = sett.height;
                    new_sett.left_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() * i + sett.left_x;
                    new_sett.right_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() + new_sett.left_x;
                    new_sett.x = (new_sett.left_x + new_sett.right_x - new_sett.width) / 2;
                    new_sett.y = sett.y + sett.height + LEVEL_STEP;
                    __initLeafs__(leafs, new_sett);
                }
            }
        }
    }

    static void __initBranches__(std::vector<sf::ConvexShape> &branches, const BTreeSettings &sett) {
        if (sett.p != nullptr) {
            sf::ConvexShape branch(4);
            branch.setFillColor(sf::Color(94, 0, 0));

            BTreeSettings new_sett;
            for (std::size_t i = 0; i < sett.p->child_nodes.size(); i++) {
                auto p = sett.p->child_nodes.at(i);
                if (p != nullptr) {
                    new_sett.p = p;
                    new_sett.width = sett.height * p->values.size() * 1.2;
                    new_sett.height = sett.height;
                    new_sett.left_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() * i + sett.left_x;
                    new_sett.right_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() + new_sett.left_x;
                    new_sett.x = (new_sett.left_x + new_sett.right_x - new_sett.width) / 2;
                    new_sett.y = sett.y + sett.height + LEVEL_STEP;

                    branch.setPoint(0, sf::Vector2f(sett.x + sett.height * 1.15 * i, sett.y + sett.height));
                    branch.setPoint(1, sf::Vector2f(branch.getPoint(0).x + 2, branch.getPoint(0).y + 2));

                    branch.setPoint(2, sf::Vector2f(new_sett.x + new_sett.width / 2, branch.getPoint(0).y + LEVEL_STEP));
                    branch.setPoint(3, sf::Vector2f(branch.getPoint(2).x - 2, branch.getPoint(2).y - 2));
                    branches.push_back(branch);

                    __initBranches__(branches, new_sett);
                }
            }
        }
    }

    static void __initText__(std::vector<sf::Text> &numbers, const sf::Font &font, const BTreeSettings &sett, const std::locale &loc) {
        if (sett.p != nullptr) {
            std::string str;
            for (const T &val : sett.p->values) str += std::format("{} ", val);

            sf::Text number;
            number.setString(sf::String(str, loc));
            number.setFont(font);
            number.setCharacterSize(static_cast<unsigned>(sett.height));
            number.setFillColor(sf::Color::Black);
            number.setPosition(sf::Vector2f(sett.x, sett.y));
            numbers.push_back(number);

            BTreeSettings new_sett;
            for (std::size_t i = 0; i < sett.p->child_nodes.size(); i++) {
                auto p = sett.p->child_nodes.at(i);
                if (p != nullptr) {
                    new_sett.p = p;
                    new_sett.width = sett.height * p->values.size() * 1.2;
                    new_sett.height = sett.height;
                    new_sett.left_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() * i + sett.left_x;
                    new_sett.right_x = (sett.right_x - sett.left_x) / sett.p->child_nodes.size() + new_sett.left_x;
                    new_sett.x = (new_sett.left_x + new_sett.right_x - new_sett.width) / 2;
                    new_sett.y = sett.y + sett.height + LEVEL_STEP;

                    __initText__(numbers, font, new_sett, loc);
                }
            }
        }
    }

    static void __veiwTree__(TreeClassType *tree, const std::locale &loc) {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        sf::RenderWindow window(sf::VideoMode(1900, 600), "BTree", sf::Style::Default, settings);

        std::vector<ShareType> leafs;
        std::vector<sf::ConvexShape> branches;
        std::vector<sf::Text> numbers;

        std::size_t height = (window.getSize().y / tree->getHeight() - LEVEL_STEP) / 2;
        std::size_t width = height * tree->root->values.size() * 1.2;

        sf::Font font;
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

        sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
        sf::Texture background_texture;
        // background_texture.loadFromFile("tree.jpg");
        background.setTexture(&background_texture);

        BTreeSettings sett = { tree->root, width, height, (window.getSize().x - width) / 2, 0, 0, window.getSize().x };
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
            for (ShareType &leaf : leafs)
                window.draw(leaf);
            for (sf::Text &number : numbers)
                window.draw(number);

            window.display();
        }
    }

public:
    static void veiwTree(std::initializer_list<TreeClassType *> init_list, const std::locale &loc = std::locale()) {
        std::vector<std::thread> threads;
        for (TreeClassType *elem : init_list)
            threads.push_back(std::thread(__veiwTree__, elem, loc));
        for (std::thread &th : threads)
            th.join();
    }
};
