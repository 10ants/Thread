void One(Object* obj) {
    while (!obj->isThreeDone())
    {
        obj->SetNum(17);
        obj->SetWord("One");
    }
}
void Two(Object* obj) {
    while (!obj->isThreeDone())
    {
        obj->SetNum(obj->GetNum() + 13);
        obj->SetWord("Two");
    }
}
void Three(Object* obj) {
    unsigned int i = 0;
    std::cout << i << std::endl;
    while (i >= 0 && i != INT_MAX) {
        if (i == INT_MAX) {
            break;
        }
        obj->SetNum(i);
        obj->SetWord("Three");
        i++;
    }
    obj->SetThreeDone(true);
}
int main()
{
    Object* obj = new Object;
    std::thread first(One, obj);
    std::thread second(Two, obj);
    std::thread third(Three, obj);
    while (!obj->isThreeDone())
    {
        std::cout << obj->GetNum() << " " << obj->GetWord() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    first.join();
    second.join();
    third.join();
}
