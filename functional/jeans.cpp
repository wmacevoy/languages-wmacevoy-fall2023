class Jeans {
public:
    Jeans(std::string brand, std::string size, std::string color, int quantity)
        : brand(brand), size(size), color(color), quantity(quantity) {}
    
    Jeans clone() const {
        return Jeans(brand, size, color, quantity);
    }

private:
    std::string brand;
    std::string size;
    std::string color;
    int quantity;
};

class Order {
public:
    Order(int id, Jeans jeans, std::string status = "Pending")
        : id(id), jeans(jeans), status(status) {}
    
    Order clone() const {
        return Order(id, jeans.clone(), status);
    }

private:
    int id;
    Jeans jeans;
    std::string status;
};

class Warehouse {
public:
    Warehouse() {}

    void updateInventory(const Jeans& jeans) {
        std::string key = jeans.clone().brand + "-" + jeans.clone().size + "-" + jeans.clone().color;
        inventory[key] += jeans.clone().quantity;
    }

    Warehouse clone() const {
        Warehouse newWarehouse;
        newWarehouse.inventory = inventory;
        return newWarehouse;
    }

private:
    std::unordered_map<std::string, int> inventory;
};

class DistributionSystem {
public:
    DistributionSystem() : warehouse() {}

    void placeOrder(const Order& order) {
        orders.push_back(order.clone());
        warehouse.updateInventory(order.clone().jeans);
        std::cout << "Order " << order.clone().id << " placed." << std::endl;
    }

    std::string checkOrderStatus(int id) const {
        for (const auto& order : orders) {
            if (order.clone().id == id) {
                return order.clone().status;
            }
        }
        return "Order not found";
    }

    DistributionSystem clone() const {
        DistributionSystem newSystem;
        newSystem.orders = orders;
        newSystem.warehouse = warehouse.clone();
        return newSystem;
    }

private:
    std::vector<Order> orders;
    Warehouse warehouse;
};

int main() {
    DistributionSystem distributionSystem;

    // Place some orders
    distributionSystem.placeOrder(Order(1, Jeans("Levi's", "32", "Blue", 100)));
    distributionSystem.placeOrder(Order(2, Jeans("Wrangler", "34", "Black", 50)));

    // Check order status
    std::cout << "Status of Order 1: " << distributionSystem.checkOrderStatus(1) << std::endl;
    std::cout << "Status of Order 2: " << distributionSystem.checkOrderStatus(2) << std::endl;

    return 0;
}

